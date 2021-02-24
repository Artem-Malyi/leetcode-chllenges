# To enable automatic execution of powershell scripts
# >_ Set-ExecutionPolicy Unrestricted -Scope CurrentUser -Force

#
# 0. get new project name from user
#
param (
    [Parameter(Mandatory=$true)][string]$projectName,
    [Parameter(Mandatory=$true)][string][AllowEmptyString()]$link,
    [Parameter(Mandatory=$true)][string]$difficulty
)

#
# convertStringToHexBytesString
#
# Utility function for editing the Visual Studio solution file.
#
function convertStringToHexBytesString {
    param (
        [Parameter(Mandatory=$true)][string]$originalString
    )
    $encoder = [system.Text.Encoding]::UTF8
    $stringBytes = $encoder.GetBytes($originalString)
    $newString = $stringBytes.ForEach('ToString', 'X') -join ' '
    return $newString
}

#
# 1. Validate input
#

$number, $name = $projectName.split('.')
if (!$name) {
  $name = $projectName
  $number = "---"
}
else {
  $name = $name.Trim()
}
$folderName = if ($number.equals("---"))
  { $($name -replace " ", '-').ToLower() } else
  { $($number + "-" + $name -replace " ", '-').ToLower() }
if ([string]::IsNullOrEmpty($link)) {
   $link = "Didn't find it on LeetCode"
}

#
# 1. Copy sample project to the given location
#
"1. Copy sample project to the given location"
$solutionDir = $PSScriptRoot + '\..'
$sourceProjectFile = $($solutionDir + '\src\challenge1\challenge1.vcxproj')
$sourceCppFile = $($solutionDir + '\src\challenge1\main.cpp')
$destinationProjectFile = $sourceProjectFile -replace 'challenge1', $folderName
$destinationCppFile = $sourceCppFile -replace 'challenge1', $folderName
md -Path $($solutionDir + '\src\' + $folderName) -Force
cp -Path $sourceProjectFile -Destination $destinationProjectFile
cp -Path $sourceCppFile -Destination $destinationCppFile

#
# 2. Update readme file
#
"2. Update readme file"
$difficulty = (Get-Culture).TextInfo.ToTitleCase($difficulty.ToLower())
$newReadmeEntry = $number + " | " + $name + " | " + $difficulty + " | [Solution](src/" + $folderName + "/main.cpp)"
Add-Content -Path $($solutionDir + "\readme.md") -Value $newReadmeEntry

#
# 3. Update source file
#
"3. Update source file"
(Get-Content $destinationCppFile) | Foreach-Object {
 $_ -replace "hyperlink to the leetcode problem", $link`
    -replace "name of the problem", $projectName`
} | Set-Content $destinationCppFile -Force

#
# 4. Update the name and guid of the new project file
#
"4. Update the name and guid of the new project file"
$guidRegex = "[a-fA-F0-9]{8}-([a-fA-F0-9]{4}-){3}[a-fA-F0-9]{12}"
$newGuid = $(New-Guid).Guid
(Get-Content $destinationProjectFile) | Foreach-Object {
 $_ -replace "challenge1", $folderName`
    -replace $guidRegex, $newGuid`
} | Set-Content $destinationProjectFile -Force

#
# 5. Add new name and guid to solution file, as follows:
#
#Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "904-Fruits-Into-Baskets", "..\src\904-Fruits-Into-Baskets\904-Fruits-Into-Baskets.vcxproj", "{DDC1EF41-050F-4BD5-A74D-9DCC58F0FF75}"
#EndProject
"5. Add new name and guid to solution file"
$solutionFile = $($solutionDir + '\make\leetcode-challenges.sln')

$solutionFileContent = Get-Content $solutionFile
$allGuids = $solutionFileContent | Select-String -Pattern $guidRegex -AllMatches | Select-Object -ExpandProperty Matches | Select-Object -ExpandProperty Value
$firstProjectGuid = $allGuids[0]
$newProjectString = $('Project("{' + $firstProjectGuid + '}") = "' + $folderName + '", "..\src\' + $folderName + '\' + $folderName + '.vcxproj", "{' + $newGuid + '}"')

# Read the entire file content as a [byte[]] array.
# Note: Use PowerShell *Core* syntax.
# In *Windows PowerShell*, replace `-AsByteStream` with `-Encoding Byte`
# `-Raw` ensures that the file is efficiently read as [byte[]] array at once.
$byteArray = Get-Content $solutionFile -Raw -Encoding Byte

# Convert the byte array to a single-line "byte string",
# where the whitespace-separated tokens are the hex. encoding of a single byte.
# If you want to guaranteed that even byte values < 0x10 are represented as
# *pairs* of hex digits, use 'X2' instead.
$byteString = $byteArray.ForEach('ToString', 'X') -join ' '

# Convert search string into a single-line "byte string".
$searchByteString = convertStringToHexBytesString("EndProject`r`nGlobal")

# Convert newly generated string into a single-line "byte string".
$newByteString = convertStringToHexBytesString($("EndProject`r`n" + $newProjectString + "`r`nEndProject`r`nGlobal"))

# Perform the replacement.
# Note that since the string is guaranteed to be single-line,
# inline option `(?s)` isn't needed.
# Also note how the hex-digit sequences representing bytes are also separated
# by spaces in the search and replacement strings.
$byteString = $byteString -replace $searchByteString, $newByteString

# Convert the byte string back to a [byte[]] array, and save it to the
# target file.
# Note how the array is passed as an *argument*, via parameter -Value,
# rather than via the pipeline, because that is much faster.
# Again, in *Windows PowerShell* use `-Encoding Byte` instead of `-AsByteStream`.
[byte[]] $newByteArray = -split $byteString -replace '^', '0x'
Set-Content $solutionFile -Encoding Byte -Value $newByteArray

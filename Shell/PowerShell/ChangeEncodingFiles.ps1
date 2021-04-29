# Description: Script to change file encoding

# The directory where the recursive search starts
$rootDir = "C:\Users\shemp\Study\Shell"
# File extensions for which the encoding will be changed
$extensions = @(
	"*.cpp", 
	"*.c", 
	"*.h", 
	"*.hpp"
)
# Applied encoding
# Note: utf8 - this is UTF-8 BOM for PowerShell versions below 6. For BOMless UTF-8 use custom argument 'utf8nobom'
$encoding = "utf8nobom"
# Folders in which the script will not enter recursively
$excludeFolders = @(
	"Windows"
)

Get-ChildItem -Path $rootDir -Include $extensions -Recurse | Where {$_.Fullname | select-string -notmatch $excludeFolders} | ForEach-Object {
	$fileName = $_.Fullname
	
	try {
		# [IO.File]::WriteAllTexts writes in UTF-8 encoding without BOM by default
		if ($encoding -eq "utf8nobom") {
			$rawStr = Get-Content -Raw $fileName
			
			[IO.File]::WriteAllText($fileName, $rawStr)
		}
		else {
			[Io.File]::ReadAllText($fileName) | Out-File -FilePath $fileName -Encoding $encoding -NoNewline
		
			#$content = $_ | Get-Content
			#Set-Content -PassThru $fileName $content -Encoding $encoding -Force
		}
		
		Write-Host """$fileName"" converting done." -fore green
	}
	catch {
		Write-Host "Converting ""$fileName"" failed with error: $PSItem" -fore red
	}
}  	

Read-Host -Prompt "Script done. Press Enter to exit"

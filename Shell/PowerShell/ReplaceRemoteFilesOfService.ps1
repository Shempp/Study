# Description: Script to replace files of services/processes
# For the script to work correctly, you must: 
# 	1. Enable-PSRemoting (sometimes you need a flag '–force') 
#	2. The WinRM service must be running
#	3. Сheck firewall settings for port 5985 (WinRM)
#	4. Add computer to TrustedHosts list (needed if credentials will be local not AD. It must be done on the local machine, however, it may also be needed on the remote)

# Remote machine where the files will be replaced
$hostName = "shemp.domain.local"
# Credentials for remote operations
#$username = "domain.local\admin"
#$password = "somepassword"
$username = "$hostName\Administrator"
$password = "somepassword"
$credentials = New-Object -Typename System.Management.Automation.PSCredential -ArgumentList $username, ($password | ConvertTo-SecureString -AsPlainText -Force)
# or if you need interactive input of credentials
#$credentials = Get-Credential
# Services and processes that need to be stopped to replace files
$servicesToStop = @(
	"shempService",
	"shempProcess"
)
# Folders on the local machine where files to copy are located (recursive search)
$localDirs = @(
	"D:\Develop\Bin\Debug\x64",
	"E:\Projects\Bin\debug\x64"
)
# Folders on the remote machine where the files will be replaced
$remoteDirs = @(
	"C:\Program Files\shempProgram"
)
# Files to be replaced on the remote machine
$filesToReplace = @(
	"First.exe",
	"Second.exe",
	"Third.dll",
	"Fourth.dll"
)

try {
	Write-Host "Getting services list from the remote host ""$hostName""" -Fore Green
	$remoteServices = Get-Service -ComputerName $hostName | Where-Object {$servicesToStop -contains $_.Name}
	Write-Host "Getting a list of processes from the remote host ""$hostName""" -Fore Green
	$remoteProcesses = Get-Process -ComputerName $hostName | Where-Object {$servicesToStop -contains $_.Name}
	if (!$remoteServices -and !$remoteProcesses) {
		Throw "No matching services/processes was found on ""$hostName"""
	}
	
	# Printing information about services/processes that were not found on the remote host
	$servicesToStop | Where {!($remoteServices.Name + $remoteProcesses.Name).Contains($_)} | Foreach-Object {
		Write-Host "Warning: Service/process ""$_"" was not found on ""$hostName""" -Fore Yellow
	}
	
	# Stopping services
	Foreach ($remoteService in $remoteServices) { 
		if ($remoteService.Status -eq "Running") {
			Write-Host "Stopping service ""$($remoteService.Name)"" on ""$hostName""" -Fore Green
			$remoteService.Stop()
			$remoteService.WaitForStatus("Stopped", "00:00:05")
		}
		else {
			Write-Host "Warning: Service ""$($remoteService.Name)"" has already been stopped in ""$hostName""" -Fore Yellow
		}
	}
	
	# Since credentials are in any case needed to replace files on a remote machine, we do not use WMI for stopping the process for now
	<#
	Foreach ($remoteProcess in $remoteProcesses) { 
		Write-Host "Stopping process ""$($remoteProcess.Name)"" in ""$hostName""" -Fore Green
		$processByWMI = Get-WmiObject -Class Win32_Process -ComputerName $hostName -Filter "ProcessID ='$($remoteProcess.Id)'"
		if ($processByWMI) {
			if ($processByWMI.Terminate().returnValue -ne 0) {
				Write-Host "Error when stopping process ""$($remoteProcess.Name)"" in ""$hostName"" with WMI" -Fore red
			}
		} 
		else {
			Write-Host "Process ""$($remoteProcess.Name)"" not found in ""$hostName"" with WMI" -Fore Yellow
		}
	}
	#>
	
	# You can remove the parameter '-Authentication Negotiate' if a domain account is used (not necessary)
	$session = New-PSSession -ComputerName $hostName -Credential $credentials -Authentication Negotiate
	Invoke-Command -Session $session -ArgumentList $remoteProcesses, $hostname -ScriptBlock {
		Param($remoteProcesses, $hostname)
		# Stopping processes
		Foreach ($remoteProcess in $remoteProcesses) {
			if (!$remoteProcess.HasExited) {
				Write-Host "Stopping process ""$($remoteProcess.Name)"" in ""$hostName""" -Fore Green
				$remoteProcess | Stop-Process -Force
				$remoteProcess | Wait-Process
			}
		}	
	}
	
	# Looking for files on the local machine
	$localFiles = Get-ChildItem -Path $localDirs -Recurse -ErrorAction SilentlyContinue -Force | Where-Object {$filesToReplace -contains $_.Name}
	if (!$localFiles) {
		Throw "No matching files was found on local machine"
	}
	# Printing information about files on the local machine that were not found
	$filesToReplace | Where {!($localFiles.Name).contains($_)} | Foreach-Object {
		Write-Host "Warning: File ""$_"" was not found on the local machine in the specified folders ""$localDirs"". It will be ignored" -Fore Yellow
	}
	
	# Looking for files on the remote machine
	$matchFiles = Invoke-Command -Session $session -ArgumentList $remoteDirs, $filesToReplace, $localFiles, $hostname -ScriptBlock {
		Param($remoteDirs, $filesToReplace, $localFiles, $hostname)
		$remoteFiles = Get-ChildItem -Path $remoteDirs -Recurse -ErrorAction SilentlyContinue -Force | Where-Object {$filesToReplace -contains $_.Name}
		if (!$remoteFiles) {
			Throw "No matching files was found on ""$hostName"" in the specified folders ""$remoteDirs"""
		}
		
		$foundedFiles = New-Object System.Collections.ArrayList
		Compare-Object $localFiles $remoteFiles -Property Name -IncludeEqual | Foreach-Object {
			# '<=' - in this context means that the file was not found on the remote machine
			if ($_.SideIndicator -eq "<=") {
				Write-Host "Warning: File ""$($_.Name)"" was not found on the remote machine ""$hostName"" in the specified folders ""$remoteDirs"". It will be ignored" -Fore Yellow
			}
			elseif ($_.SideIndicator -eq "==") {
				$nameOfFile = $_.Name
				$remoteFile = $remoteFiles | Where {$_.Name -eq $nameOfFile}
				Remove-Item $remoteFile.FullName
				[void]$foundedFiles.Add($remoteFile)
			}
		}
		
		return $foundedFiles
	}
	
	# Replace existing files
	$matchFiles | Foreach-Object {
		$matchName = $_.Name
		$localFile = $localFiles | Where {$_.Name -eq $matchName}
		Write-Host "Copying file ""$localFile"" from localhost to ""$_"" in ""$hostName""" -Fore Green
		Copy-Item -Path $localFile.FullName -Destination $_.FullName -Force -ToSession $session
	}
	
	# Start services
	Foreach ($remoteService in $remoteServices) { 
		if ($remoteService.Status -eq "Stopped") {
			Write-Host "Starting service ""$($remoteService.Name)"" in ""$hostName""" -Fore Green
			$remoteService.Start()
			$remoteService.WaitForStatus("Running", "00:00:05")
		}
		else {
			Write-Host "Warning: Service ""$($remoteService.Name)"" already started in ""$hostName""" -Fore Yellow
		}
	}
	
	# We do not start processes (because there may be different flags, in contrast to the installed services)
}
catch {
	Write-Host "Error: $PSItem" -Fore Red
}
finally {
	if ($session) {
		$session | Remove-PSSession
	}
	Read-Host -Prompt "Script done. Press Enter to exit"
}	
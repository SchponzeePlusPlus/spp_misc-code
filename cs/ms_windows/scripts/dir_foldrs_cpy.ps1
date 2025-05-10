<#
	Script description.

	Some notes.

	Get-ExecutionPolicy -List
	Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process
	Get-ExecutionPolicy -List
#>

param (
    # xx
    [Parameter(Mandatory=$true)]
    [string]$Dir_src,
    
    # xx
    #[string]$Dir_dest = 'c:\\_Test'
	[string]$Dir_dest = "$PSScriptRoot\Output"
	)

# This is an automatic variable set to the current file's/module's directory
cd $PSScriptRoot

ls

echo $Dir_src

echo $Dir_dest

# -Confirm: Prompts you for confirmation before running the cmdlet.

# -Force: Indicates that this cmdlet copies items that can't otherwise be changed, such as copying over a read-only file or alias.

# -Recurse: Indicates that this cmdlet does a recursive copy.

# PSIsContainer is a property of the current object that returns true or false depending on if it is a folder or not.

#Copy-Item -Path " $Dir_src + '\*' " -Destination $Dir_dest -Confirm -Force -Recurse -Verbose
Copy-Item -Path $Dir_src -Destination $Dir_dest -Filter {PSIsContainer} -Confirm -Force -Recurse -Verbose
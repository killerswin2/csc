param (
	[string]$installPath = ""
)
$installPath

if($installPath -eq "")
{
	Exit
} 
else
{
	if(Test-Path -Path $installPath)
	{
		"installing files"
		$copyPath = "$PSScriptRoot\build\win64\csc_x64.dll"
		Copy-Item -Path $copyPath -Destination "$installPath\intercept\csc_x64.dll" -Force
	}

}
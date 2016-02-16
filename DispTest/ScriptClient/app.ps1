$assemblyPath = Resolve-Path ..\Debug\StringLib.dll
$null = [Reflection.Assembly]::LoadFile($assemblyPath)
$myobj = New-Object StringLib.StringObjClass
$null = Register-ObjectEvent -InputObject $myobj -EventName OnConcatResult -Action { Write-Host "callback result: ", $event.SourceArgs[0] }
$result = $myobj.Concat("hello ", "world")
Write-Host "normal result" , $result

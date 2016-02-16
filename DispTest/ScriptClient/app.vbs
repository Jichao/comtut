'run with 32bit cscript
Function myObj_OnConcatResult(value1)
	WScript.Echo "callback result" & value1
End Function

set myObj = WScript.CreateObject("DispTest.String.1", "myObj_")
result = myObj.Concat("Hello","World")
WScript.Echo "normal result" & result

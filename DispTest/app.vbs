Function myObj_OnConcatResult(value1)
	WScript.Echo "callback result" & value1
End Function

set myObj = WScript.CreateObject("DispTest.String.1", "myObj_")
result = myObj.Concat("Hello","World")
'myObj.OnConcatResult = GetRef("ShowResult")
'myObj.ConnectObject myObj, "myObj_"
WScript.Echo result

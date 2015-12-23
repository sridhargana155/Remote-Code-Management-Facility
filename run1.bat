:run1.bat

:Text file upload

"Debug/Executive.exe" SourcePort 9080 DestnPort 9081 UploadFilename Sample2.cpp DownloadFilename Sample1.h Path ./Server/Repository/ Category Header_Files Pattern *.h Textsearch class
:run2.bat

:Binary File upload

"Debug/Executive.exe" SourcePort 1020 DestnPort 1021 UploadFilename Sample3.cpp DownloadFilename Sample4.h Path ./Server/Repository/ Category Header_Files Pattern *.h Textsearch class
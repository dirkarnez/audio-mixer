@REM run as Administrator
@echo off
cd /d %~dp0
set DOWNLOADS_DIR=%USERPROFILE%\Downloads
set DOWNLOADS_DIR_LINUX=%DOWNLOADS_DIR:\=/%

SET PATH=^
%DOWNLOADS_DIR%\ffmpeg-6.0-full_build-shared\ffmpeg-6.0-full_build-shared\bin;^
%SystemRoot%\System32;

cd %~dp0../cmake-build/ && audio-mixer.exe

pause

cd %~dp0

del /s /q *.pcm

ffmpeg -i "440Hz.wav" -i "560Hz.wav" -i "880Hz.wav" -filter_complex amix=inputs=3:duration=first:dropout_transition=3:normalize=0 -c:a pcm_s16le "ffmpeg-sum.wav" &&^
ffmpeg -i ffmpeg-sum.wav -acodec pcm_s16le -f s16le ffmpeg-sum.pcm &&^
ffmpeg -i output.wav -acodec pcm_s16le -f s16le output.pcm 

pause

fc /b ffmpeg-sum.pcm output.pcm
pause
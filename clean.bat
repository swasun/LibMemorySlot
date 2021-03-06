@echo "Removing bin release files"
powershell -Command "Remove-Item 'bin\release\*' -Recurse -Force"
@echo "Removing bin debug files"
powershell -Command "Remove-Item 'bin\debug\*' -Recurse -Force"
@echo "Removing build release files"
powershell -Command "Remove-Item 'build\release\*' -Recurse -Force"
@echo "Removing build debug files"
powershell -Command "Remove-Item 'build\debug\*' -Recurse -Force"
@echo "Removing out files"
powershell -Command "Remove-Item 'out\*' -Recurse -Force"
@echo "Done"

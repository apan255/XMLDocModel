@echo off
cls

echo ***** Demonstrating Requirement 11 And 3 with file  *****
echo ***** File: "../../TEST_FOLDER_XMLDocument/LectureNote.xml" *****
".\XMLDocument\Debug\Executive.exe" "/f" "./TEST_FOLDER_XMLDocument/LectureNote.xml"

echo ***** Demonstrating Requirement 11 And 3 with string *****
echo ***** String: "<?xml version=\"1.0\"  encoding=\"utf - 8\"> <LectureNote course = \"CSE681\"  NewAttribute = \"Value\"> <title> XML Example # 1 </title> </LectureNote>" *****
".\XMLDocument\Debug\Executive.exe" "/s" "<?xml version=\"1.0\"  encoding=\"utf - 8\"?> <LectureNote course = \"CSE681\"  NewAttribute = \"Value\"> <title> XML Example # 1 </title> </LectureNote>"

24-783 Special Topics: Advanced Engineering Computation
Spring 2017 Carnegie Mellon University
Instructor: Soji Yamakawa
=======================================================
Team information
=======================================================
Name: iBelieve
Fangcheng Zhu (fangchez)
Zewen Wang (zewenw)
Ximing Li (ximingl)
Yihui Wang (yihuiw)
Zao Lou (zlou)
=======================================================
Goal & Schedual
=======================================================
2/19/2017 -- 2/26/2017
1.GUI design
2.Open/save file
3.Text linked list data structure
4.Other basic functions
required classes:
Menu
-File(new open save close) -Edit(search replace select)
-Compile() -Help(documentation about)
=======================================================
Tutorial
=======================================================
Windows:
1.Everytime before you start working on files, run svn update
to download the latest version of code.
2.After you do local modification, make sure everything is ok
and then commit to upload the files.
3.Do not forget to modify related CMakeLists.txt if necessary
4.When you want to run the program, create another folder outside
iBelieve and run cmake.
5.If success, run (example)
msbuild .\Project.sln /p:Configuration=Release /p:Platform=Win32 /target:PROJECTNAME
to compile the program.
6.Enter target release folder to get .exe files

MacOS:
1~4 Same

Linux/Unix:
1~4 Same

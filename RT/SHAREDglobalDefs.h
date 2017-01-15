/*******************************************************************************
 *
 * File Name: SHAREDglobalDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a6c 07-May-2012
 * Preconditions: Assume Linux EL5 or Windows XP or is installed
 *
 * 1. Object Recognition Software Installation Instructions;
 *
 *	Install External Package 1 - Heitger Feature Detection
 *  	{FD v0.5b/c executable (Eg Linux El5.4: FD.exe [linux], Windows: FD.exe [win])
 *		"heitger feature detection with RBB Endian Mod v0.5b" is
 *		olof Henricsson 96-06-07 release of Friedrich Heitger's SE binary with
 *			a) ras format endian swap, b) ras format relaxed,
 *			c) multiple endian outputs for Keypoints exe, d) Windows VS compatibility,
 *			e) change of binary name from SE to FD.exe};
 *
 *		(Linux EL5 Only)
 *		copy (Linux EL5 x86_64 compiled) FD.exe to OR.exe working folder
 *
 *		(Linux EL6 Only)
 *		copy (Linux EL6 x86_64 compiled) FD.exe to OR.exe working folder
 *
 *		(Windows Only)
 *		copy (Windows XP i386 compiled) FD.exe to OR.exe working folder
 *
 *		(Windows 7 x86_64 Only)
 *		copy (Windows 7 x86_64 compiled) FD.exe to OR.exe working folder
 *
 *	Install External Package 2 - Freeglut;
 *
 *		(Linux EL5 Only)
 *		rpm -i freeglut-2.4.0-7.1.el5.x86_64.rpm
 *
 *		(Linux EL6 Only)
 *		rpm -i freeglut-2.6.0-1.el6.x86_64.rpm
 *
 *		(Windows XP Only)
 *		unzip freeglut 2.4.0 (compiled).zip
 *				copy freeglut.dll from freeglut 2.4.0 (compiled).zip to c:\Windows\System32
 *
 *		(Windows 7 x86_64 Only)
 *		unzip freeglut 2.6.0 (compiled).zip
 * 			copy freeglut.dll from freeglut 2.6.0 (compiled) - 32bit.zip to: C:\WINDOWS\SysWOW64 [or System32]
 *
 *	Install External Package 3 - ImageMagik;
 *
 *		(Linux EL5 Only)
 *		rpm -i ImageMagick-c++-6.2.8.0-4.el5_1.1.x86_64.rpm
 *
 *		(Linux EL6 Only)
 *		rpm -i ImageMagick-c++-6.5.4.7-5.el6.x86_64.rpm
 *
 *		(Windows XP Only)
 *		install  ImageMagick-6.5.5-4-Q16-windows-dll.exe
 *
 *		(Windows 7 x86_64 Only)
 *		install ImageMagick-6.7.2-1-Q16-windows-x64-dll.exe (use default settings)
 *
 *	Install External Package 4 - JPEG development libraries (Independent JPEG Group)
 *
 *		(Linux EL5 Only)
 *		Use preinstalled EL5 Linux JPEG libraries;
 *		rpm -i libjpeg-6b-37.x86-64.rpm
 *		rpm -i libjpeg-devel-6b-37.x86-64.rpm
 *
 *		(Linux EL6 Only)
 *		Use preinstalled EL5 Linux JPEG libraries;
 *		rpm -i libjpeg-6b-46.el6.x86_64.rpm
 *		rpm -i libjpeg-devel-6b-46.el6.x86_64.rpm
 *
 *		(Windows XP Only)
 *		Is there any?
 *		copy jpeg.lib in JPEG\Release folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\lib\
 *		copy jpeglib.h, jconfig.h, and jmorecfg.h in JPEG folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\Include\
 *		ensure jpeg.lib is added to MS Visual Studio OR project - Linker - additional dependencies
 *
 *		(Windows 7 x86_64 Only)
 *		Is there any?
 *		copy jpeg.lib in JPEG\Release folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\lib\
 *		copy jpeglib.h, jconfig.h, and jmorecfg.h in JPEG folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\Include\
 *		ensure jpeg.lib is added to MS Visual Studio OR project - Linker - additional dependencies
 *
 * Install External Package 5 - MySQL Server;
 *
 *		5. Part a)
 *
 *		(Linux EL5 Only) On the MySQL Server perform the following actions to initiate the server;
 *		rpm -i mysql-5.0.77-3.el5.x86_64.rpm
 *		rpm -i mysql-server-5.0.77-3.el5.x86_64.rpm
 *		chkconfig mysqld on
 *		/etc/init.d/mysqld start
 *		mysqladmin -u root password chooseamysqlrootpassword
 *
 *		(Linux EL6 x86_64 Only) On the MySQL Server perform the following actions to initiate the server;
 *		rpm -i mysql-5.1.47-4.el6.x86_64.rpm
 *		rpm -i mysql-server-5.1.47-4.el6.x86_64.rpm
 *		chkconfig mysqld on
 *		/etc/init.d/mysqld start
 *		mysqladmin -u root password chooseamysqlrootpassword
 *
 *				OLD: (Windows 7 x86_64 Only) On the MySQL Server perform the following actions to initiate the server;
 *				For example. install mysql-installer-5.5.15.0.msi
 *					set to 32bit - NB this assumes Microsoft Visual Studio Express [2008/2010] with 32bit only compilation
 *					Select Defaults (developer install)...
 *					set password
 *
 *		(Windows XP Only) On the MySQL Server perform the following actions to initiate the server;
 *		For example. install mysql-5.1.41-win32.msi
 *			{During installation perform the following configurations; select 'c include files / libraries' [for development], and select 'include bin directory in Windows PATH'}
 *			Click Next
 *			Select 'Custom' setup type. Click Next
 *			Select Developer Components 'C Include Files / Lib Files' - This feature and All subfeatures, will be installed on local hard drive. Click Next.
 *			Click Install
 *			Click Next, Click Next
 *			Leave 'Configure the MySQL Server Now' option ticked. Untick 'Register the MySQL Server now' button. click Next.
 *			Leave 'Detailed Configuration' selected. Click Next
 *			Leave 'Developer Machine' selected. Click Next
 *			Leave 'Multifunctional database' selected. Click Next
 *			Leave default installation path selected. Click Next
 *			Leave 'Decision Support' selected and leave '15 concurrent connections' selected. Click Next
 *			Leave 'Enable TCP/IP Networking' selected. Untick 'Add firewall exception for this port' (unless require network access). Leave 'Enable Strict Mode' selected. Click Next
 *			Leave 'Standard character set' selected. Click Next
 *			Select 'Include Bin Directory in Windows PATH'. Leave 'Install As Window Service', service name MySQL, and 'Launch the MySQL Server automatically' selected. Click Next
 *			Leave 'Modify Security Settings' selected, and enter a root password, chooseamysqlrootpassword (do not select 'enable root access from remote machines'). Click Next.
 *			Click Execute
 *			Click Finish
 *		the MySQL server should be initiated during installation, and a root password should be assigned
 *		Copy C:\Program Files\MySQL\MySQL Server 5.1\lib\libmysql.dll to working folder (location of OR.exe)
 *			[NB on Windows XP, may need to place MySQL libraries in ... otherwise follow development installation instructions]
 *
 *		(Windows 7 x86_64 Only) On the MySQL Server perform the following actions to initiate the server;
 *		For example. install mysql-5.5.15-win32.msi (NB 32 bit mysql installation is required assuming Microsoft Visual Studio Express [2008/2010] with 32bit only compilation)
 *			{During installation ensure the following configurations; select 'c include files / libraries' [for development], and select 'include bin directory in Windows PATH'}
 *			Click Next
 *			Select 'Custom' setup type. Click Next
 *			Select Developer Components 'Client C API' - will be installed on local hard drive. Click Next.
 *			Click Install
 *			Click Next, Click Next, etc to Advertisments
 *			Leave 'Configure the MySQL Server Now' option ticked.  click Finish.
 *			Click Next
 *			Leave 'Detailed Configuration' selected. Click Next
 *			Leave 'Developer Machine' selected. Click Next
 *			Leave 'Multifunctional database' selected. Click Next
 *			Leave default installation path selected. Click Next
 *			Leave 'Decision Support' selected and leave '15 concurrent connections' selected. Click Next
 *			Leave 'Enable TCP/IP Networking' selected. Leave Unticked 'Add firewall exception for this port' (unless require network access). Leave 'Enable Strict Mode' selected. Click Next
 *			Leave 'Standard character set' selected. Click Next
 *			Select 'Include Bin Directory in Windows PATH'. Leave 'Install As Window Service', service name MySQL, and 'Launch the MySQL Server automatically' selected. Click Next
 *			Leave 'Modify Security Settings' selected, and enter a root password, chooseamysqlrootpassword (do not select 'enable root access from remote machines'). Click Next.
 *			Click Execute
 *			Click Finish
 *		the MySQL server should be initiated during installation, and a root password should be assigned
 *		Copy C:\Program Files (x86)\MySQL\MySQL Server 5.5\lib\libmysql.dll to working folder (location of OR.exe)
 *
 *		5. Part b)
 *
 *		(Linux or Windows) load the BAI template tables into the MySQL server's objectRecog database:
 *
 *		Either A) create them automatically using the following method;
 * 			Open Command Line
 *				Linux:
 *					open terminal (system - gnome-terminal)
 *					cd c:\home\user\source\source\
 *					mysql -u root -p < createBAImysqlDatabase.sql
 *				Windows
 *					open command prompt (Start - All Programs - Accessories - Command Prompt)
 *					mysql -u root -p < createBAImysqlDatabase.sql
 *					restart computer
 *
 *					(where createBAImysqlDatabase.sql contains the following text;)
 *
 *				CREATE DATABASE objectRecog;
 *				CREATE USER 'rich'@'localhost' IDENTIFIED BY 'Esteban7';
 *				GRANT ALL ON *.* TO 'rich'@'localhost';
 *				use objectRecog;
 *
 *				CREATE TABLE s (ID BIGINT, PRIMARY KEY (ID));
 *				ALTER TABLE s ADD COLUMN objectName TEXT;
 *				ALTER TABLE s ADD COLUMN objectNum BIGINT;
 *				ALTER TABLE s ADD COLUMN vNum SMALLINT;
 *				ALTER TABLE s ADD COLUMN zNum TINYINT;
 *				ALTER TABLE s ADD COLUMN pNum INT;
 *				ALTER TABLE s ADD COLUMN sNum TINYINT;
 *				ALTER TABLE s ADD COLUMN pBIndex1 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT1 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT1 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT1 FLOAT;
 *				ALTER TABLE s ADD COLUMN px1 FLOAT;
 *				ALTER TABLE s ADD COLUMN py1 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz1 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex2 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT2 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT2 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT2 FLOAT;
 *				ALTER TABLE s ADD COLUMN px2 FLOAT;
 *				ALTER TABLE s ADD COLUMN py2 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz2 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex3 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT3 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT3 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT3 FLOAT;
 *				ALTER TABLE s ADD COLUMN px3 FLOAT;
 *				ALTER TABLE s ADD COLUMN py3 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz3 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex4 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT4 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT4 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT4 FLOAT;
 *				ALTER TABLE s ADD COLUMN px4 FLOAT;
 *				ALTER TABLE s ADD COLUMN py4 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz4 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex5 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT5 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT5 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT5 FLOAT;
 *				ALTER TABLE s ADD COLUMN px5 FLOAT;
 *				ALTER TABLE s ADD COLUMN py5 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz5 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex6 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT6 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT6 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT6 FLOAT;
 *				ALTER TABLE s ADD COLUMN px6 FLOAT;
 *				ALTER TABLE s ADD COLUMN py6 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz6 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex7 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT7 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT7 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT7 FLOAT;
 *				ALTER TABLE s ADD COLUMN px7 FLOAT;
 *				ALTER TABLE s ADD COLUMN py7 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz7 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex8 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT8 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT8 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT8 FLOAT;
 *				ALTER TABLE s ADD COLUMN px8 FLOAT;
 *				ALTER TABLE s ADD COLUMN py8 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz8 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex9 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT9 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT9 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT9 FLOAT;
 *				ALTER TABLE s ADD COLUMN px9 FLOAT;
 *				ALTER TABLE s ADD COLUMN py9 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz9 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBIndex10 TINYINT;
 *				ALTER TABLE s ADD COLUMN pxT10 FLOAT;
 *				ALTER TABLE s ADD COLUMN pyT10 FLOAT;
 *				ALTER TABLE s ADD COLUMN pzT10 FLOAT;
 *				ALTER TABLE s ADD COLUMN px10 FLOAT;
 *				ALTER TABLE s ADD COLUMN py10 FLOAT;
 *				ALTER TABLE s ADD COLUMN pz10 FLOAT;
 *				ALTER TABLE s ADD COLUMN pBinx1 TINYINT;
 *				ALTER TABLE s ADD COLUMN pBiny1 TINYINT;
 *				ALTER TABLE s ADD COLUMN pBinx2 TINYINT;
 *				ALTER TABLE s ADD COLUMN pBiny2 TINYINT;
 *				ALTER TABLE s ADD COLUMN pBinx3 TINYINT;
 *				ALTER TABLE s ADD COLUMN pBiny3 TINYINT;
 *				ALTER TABLE s ADD COLUMN pBinxy INT;
 *				ALTER TABLE s ADD COLUMN caABin TINYINT;
 *				ALTER TABLE s ADD COLUMN caBBin TINYINT;
 *				ALTER TABLE s ADD COLUMN caCBin TINYINT;
 *				ALTER TABLE s ADD COLUMN caBin INT;
 *				ALTER TABLE s ADD COLUMN d0 TINYINT;
 *				ALTER TABLE s ADD COLUMN d1 TINYINT;
 *				ALTER TABLE s ADD COLUMN d2 TINYINT;
 *				ALTER TABLE s ADD COLUMN d3 TINYINT;
 *				ALTER TABLE s ADD COLUMN d4 TINYINT;
 *				ALTER TABLE s ADD COLUMN d5 TINYINT;
 *				ALTER TABLE s ADD COLUMN d6 TINYINT;
 *				ALTER TABLE s ADD COLUMN d7 TINYINT;
 *				ALTER TABLE s ADD COLUMN d8 TINYINT;
 *				ALTER TABLE s ADD COLUMN d9 TINYINT;
 *				ALTER TABLE s ADD COLUMN d10 TINYINT;
 *				ALTER TABLE s ADD COLUMN d11 TINYINT;
 *				ALTER TABLE s ADD COLUMN d12 TINYINT;
 *				ALTER TABLE s ADD COLUMN d13 TINYINT;
 *				ALTER TABLE s ADD COLUMN d14 TINYINT;
 *				ALTER TABLE s ADD COLUMN d15 TINYINT;
 *				ALTER TABLE s ADD COLUMN dBin BIGINT;
 *				ALTER TABLE s ADD COLUMN alltext TEXT;
 *				ALTER TABLE s ADD COLUMN colAvgBin BIGINT;
 *
 *				CREATE TABLE st LIKE s;
 *
 *				CREATE INDEX pBinxyIndex ON s (pBinxy);
 *				CREATE INDEX colAvgBinIndex ON s (colAvgBin);
 *				CREATE INDEX dBinIndex ON s (dBin);
 *				if not using decision tree code;
 *					CREATE INDEX d0Index ON s (d0);
 *					CREATE INDEX d1Index ON s (d1);
 *					CREATE INDEX d2Index ON s (d2);
 *					CREATE INDEX d3Index ON s (d3);
 *					CREATE INDEX d4Index ON s (d4);
 *					CREATE INDEX d5Index ON s (d5);
 *					CREATE INDEX d6Index ON s (d6);
 *					CREATE INDEX d7Index ON s (d7);
 *					CREATE INDEX pBinx1Index ON s (pBinx1);
 *					CREATE INDEX pBiny1Index ON s (pBiny1);
 *					CREATE INDEX pBinx2Index ON s (pBinx2);
 *					CREATE INDEX pBiny2Index ON s (pBiny2);
 *
 *				CREATE INDEX objectNameIndex ON st (objectName(10));
 *				CREATE INDEX objectNumIndex ON st (objectNum);
 *				CREATE INDEX vNumIndex ON st (vNum);
 *				CREATE INDEX zNumIndex ON st (zNum);
 *				CREATE INDEX pNumIndex ON st (pNum);
 *				CREATE INDEX sNumIndex ON st (sNum);
 *
 *				CREATE TABLE dt (ID BIGINT, PRIMARY KEY (ID));
 *
 *				ALTER TABLE dt ADD COLUMN srID BIGINT;
 *				ALTER TABLE dt ADD COLUMN dtBin TINYTEXT;	[OLD: VARCHAR]
 *
 *				CREATE INDEX dtBinIndex ON dt (dtBin(60));
 *
 *		or B) create them manually using OpenOffice.org Base via the following method;
 * 			Open Command Line
 *				Linux:
 *					open terminal (system - gnome-terminal)
 *				Windows
 *					open command prompt (Start - All Programs - Accessories - Command Prompt)
 *			mysql -u root -p
 *			enter root password previously assigned during Mysql server installation, chooseamysqlrootpassword
 *			CREATE DATABASE objectRecog;
 *			CREATE USER 'newusername'@'localhost' IDENTIFIED BY 'newuserpassword';
 *			GRANT ALL ON *.* TO 'newusername'@'localhost';
 *			exit (exit mysql command line interface)
 *			Install OpenOffice.org Base MySQL Access Point (this is a useful procedure for developers, even if they install the mysql database via the script B);
 * 				Install Java Jave Run-time environment (JRE):
 *					Linux:
 *						rpm -i java-1.6.0-openjdk...rpm
 *						rpm -i java-1.6.0-openjdk-devel...rpm
 *					Windows
 *						install jre-6u20-windows-i586-s.exe
 *				on either Platform (windows or Linux);
 *				extract mysql-connector-java-5.1.10.zip, and copy mysql-connector-java-5.1.10-bin.jar to a permanent folder
 *				Open OpenOffice.org Base - create new database [default settings]
 *				Tools - Options - Java - Class path - Add Archive (add mysql-connector-java-5.1.10-bin.jar)
 *				Close OpenOffice.org completely (including quickstarter if Windows)
 *				Open OpenOffice.org Base
 *				Connect to an existing database (JDBC). Click Next
 *				enter Datasource URL; jdbc:mysql://localhost:3306/objectRecog. enter JDBC driver class; com.mysql.jdbc.Driver. Click 'test class'. Click Next
 *				enter mysql database username (newusername), and click 'password required'. click 'Test Connection'. Click 'Next'
 *				ensure 'Yes, register the database for me' is selected. Ensure 'open the database for editing' is selected. Click 'Next'
 *				When asked, type a OpenOffice.org Base database filename, eg 'objectRecogMySQLDatabaseOpenOfficeFrontEnd'
 *			Now create the object recognition tables;
 *			create table called 's'
 *			edit s
 *			create the following fields;
 *				ID			BigInt [BIGINT] - right click on row and select primary key
 *				objectName		Text [VARCHAR]		{maybe should be TINYTEXT in the future}
 *				objectNum		BigInt [BIGINT]
 *				vNum			Small Integer [SMALLINT]
 *				zNum			Tiny Integer [TINYINT]
 *				pNum			Integer [INT]
 *				sNum			Tiny Integer [TINYINT]
 *				repeat for Q = 1,2,3,4, ... 10;
 *					pBIndexQ	Tiny Integer [TINYINT]
 *					pxTQ		Real [FLOAT]
 *					pyTQ		Real [FLOAT]
 *					pzTQ		Real [FLOAT]
 *					pxQ			Real [FLOAT]
 *					pyQ			Real [FLOAT]
 *					pzQ			Real [FLOAT]
 *				repeat for Q = 1,2,3;
 *					pBinxQ		Tiny Integer [TINYINT]
 *					pBinyQ		Tiny Integer [TINYINT]
 *				pBinxy			Integer [INT]
 *				caABin		Tiny Integer [TINYINT]
 *				caBBin		Tiny Integer [TINYINT]
 *				caCBin		Tiny Integer [TINYINT]
 *				caBin		Integer [INT]
 *				repeat for Q = 0,2,3 ... 15;
 *					dQ			Tiny Integer [TINYINT]
 *				dBin			BigInt [BIGINT]
 *				repeat for Q = A,B,C, S = 0,1...7, T = 0,1...7;
 *					simQxSyT		Tiny Integer [TINYINT]
 *				alltext					Memo [TEXT] {16bit num characters}
 *				save and close table
 *			edit s
 *				s Design
 *					assign primary key to ID (should already be assigned)
 *					add additional indexes for pBinxy, colAvgBin, dBin
 *			copy s table, paste as st
 *			edit st
 *				st Design
 *					assign primary key to ID (should already be assigned)
 *					add additional indexes for objectName, objectNum, vNum, zNum, pNum, sNum
 *			create table called 'dt'
 *			edit dt
 *			create the following fields;
 *				ID			BigInt [BIGINT] - right click on row and select primary key
 *				srID			BigInt [BIGINT]
 *				dtBin			TINYTEXT
 *
 *
 * 2. Object Recognition Software Development Installation Instructions;
 *
 *	Unzip Source Archive
 *
 *	Ensure that all source ANSI files are either Windows/PC (ASCII) or UNIX formated
 *
 *		(Linux Only)
 *		dos2unix *.cpp *.c *.h *.ldr *.DAT *.dat *.data *.xml *.backup
 *
 *		(Windows Only)
 *		ToDos.exe *.cpp *.c *.h *.ldr *.DAT *.dat *.data *.xml *.backup
 *			[download convert.zip from http://www.textpad.com/add-ons/]
 *
 *	Install Compiler
 *
 *		(Linux Only)
 *		N/A (GCC already installed)
 *
 *		(Windows XP Only)
 *		Install MS Visual Studio C++ 2008 Express Edition (VS2008ExpressWithSP1ENUX.iso / vcsetup.exe / vcsetup2008.exe)
 *
 *		(Windows 7 x86_64 Only)
 *		Install MS Visual Studio C++ 2010 Express Edition (VS2010Express1.iso / vcsetup.exe)
 *
 *	Compile FD executable
 *
 *		(Linux Only)
 *		nedit FDdefs.h, and uncomment the LINUX preprocessor def
 *		./compileFD.bat
 *		This will create FD.exe in the current folder
 *
 *		(Windows Only)
 *		Open FD.sln using MS Visual Studio C++ 20xx Express Edition
 *		edit FDdefs.h, and comment out the LINUX preprocessor def
 *		Build All
 *		This will create FD.exe in the Release folder
 *
 *	Install Freeglut development libraries
 *
 *		(Linux EL5 Only)
 *		rpm - i freeglut-devel-2.4.0-7.1.el5.x86_64.rpm
 *
 *		(Linux EL6 Only)
 *		rpm -i freeglut-devel-2.6.0-1.el6.x86_64.rpm
 *
 *		(Windows XP Only);
 *		unpack source code freeglut 2.4.0 (compiled).zip
 *		copy freeglut.h to: C:\Program Files\Microsoft Visual Studio 9.0\VC\include\GL\ (note: you'll have to create the GL folder)
 * 		copy freeglut_ext.h to: C:\Program Files\Microsoft Visual Studio 9.0\VC\include\GL\
 * 		copy freeglut_std.h to: C:\Program Files\Microsoft Visual Studio 9.0\VC\include\GL\
 * 		copy freeglut.lib to: C:\Program Files\Microsoft Visual Studio 9.0\VC\lib\
 * 		copy freeglut.dll to: C:\WINDOWS\system32\
 *
 *		(Windows 7 x86_64 Only);
 *		unpack source code freeglut 2.6.0 (compiled) - 32bit.zip
 *		copy freeglut.h to: C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include\GL\ (note: you'll have to create the GL folder)
 * 		copy freeglut_ext.h to: C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include\GL\
 * 		copy freeglut_std.h to: C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include\GL\
 * 		copy freeglut.lib to: C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\
 * 		copy freeglut.dll to: C:\WINDOWS\SysWOW64 [or System32]
 *
 *	Install JPEG Development libraries (Independent JPEG Group)
 *
 *		(Linux EL5/EL6 Only);
 *		rpm - i libjpeg-devel-6b-37.x86-64.rpm
 *
 * 		(Windows XP / Windows 7 x86_64 Only)
 *		Build JPEG Libraries from source;
 *			Either A) unzip the BAI JPEG development package, Eg 'JPEG source - with visual studio 6 Sept 11a.zip / JPEG v7 source - with visual studio 17 April 10a.zip / JPEG source - with visual studio 12 Oct 09a.zip'
 *				copy jconfig.h.microsoftvisualstudio jconfig.h (ie, overwrite jconfig.h with jconfig.h.microsoftvisualstudio)
 *			Or B);
 *				unpack source code jpegsrc.v7.zip
 *				copy jconfig.h.microsoftvisualstudio jconfig.h (ie, overwrite jconfig.h with jconfig.h.microsoftvisualstudio)
 *				rename makeasln.vc9 to JPEG.sln
 *				rename makecvcp.vc9 to cjpeg.vcproj
 *				rename makedvcp.vc9 to djpeg.vcproj
 *				rename maketvcp.vc9 to jpegtran.vcproj
 *				rename makervcp.vc9 to rdjpgcom.vcproj
 *				rename makewvcp.vc9 to wrjpgcom.vcproj
 *				rename makecvcp.vc9 to jpeg.vcproj
 *				create example.vcproj
 *				open JPEG.sln and edit it to include all of the above projects [make copies of those that already exist and modify them accordingly]
 *			open JPEG.sln
 *			Build All
 * 			(this will create a jpeg.lib in the primary Release folder, and create example.exe)
 *			copy jpeg.lib in JPEG\Release folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\lib\
 *			copy jpeglib.h, jconfig.h, and jmorecfg.h in JPEG folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\Include\
 *			ensure jpeg.lib is added to MS Visual Studio OR project - Linker - additional dependencies
 *
 *	Install MySQL Development Libraries
 *
 *		(Linux EL5 Only)
 *		rpm -i mysql-devel-5.0.77-3.el5.x86_64.rpm
 *		(MySQL development libraries already installed?)
 *
 *		(Linux EL6 Only)
 *		rpm -i mysql-devel-5.1.52-1.el6_0.1.i686.rpm
 *
 *		(Windows XP Only)
 *		copy C:\Program Files\MySQL\MySQL Server 5.1\lib\libmysql.lib and libmysql.dll to C:\Program Files\Microsoft Visual Studio 9.0\VC\Lib\
 *		create folder C:\Program Files\Microsoft Visual Studio 9.0\VC\Include\mysql\
 *		copy all files in C:\Program Files\MySQL\MySQL Server 5.1\include\ folder to C:\Program Files\Microsoft Visual Studio 9.0\VC\Include\mysql\
 *		ensure libmysql.lib is added to MS Visual Studio OR project - Linker - additional dependencies
 *		Copy C:\Program Files\MySQL\MySQL Server 5.1\lib\libmysql.dll to working folder (location of OR.exe)
 *
 *		(Windows 7 x86_64 Only)
 *		copy C:\Program Files (x86)\MySQL\MySQL Server 5.5\lib\libmysql.lib and libmysql.dll to C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\
 *		create folder C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include\mysql\
 *		copy all files in C:\Program Files (x86)\MySQL\MySQL Server 5.5\include\ folder to C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include\mysql\
 *		ensure libmysql.lib is added to MS Visual Studio OR project - Linker - additional dependencies
 *		Copy C:\Program Files (x86)\MySQL\MySQL Server 5.5\lib\libmysql.dll to working folder (location of OR.exe)
 *
 *	Compile OR.exe
 *
 *		(Linux Only)
 *		open SHAREDglobalDefs.h, and ensure #define LINUX is added
 *		copy makefile.OR makefile
 *		./clear.bat (rm *.o)
 *		make
 *
 *		(Windows Only)
 *		open SHAREDglobalDefs.h, and ensure #define LINUX is commented out
 *		Open OR.sln
 *		Build All
 *
 * Post Conditions;
 *
 *  	depends upon project being compiled (OR, RT, ANN, CS, FD, etc)
 *
 * Important preprocessor definitions to consider before compilation;
 *
 *		#define LINUX
 *
 * Release Notes;
 *
 * - [2a1x]
 * - [2a2x]
 * - [2a3x] feature.cpp centre features implementation
 * - [2a4x] CS.exe upgrade
 * - [2a5x] feature.cpp centre features have now been implemented - however still need to implement 3DOD min max detection on surfaces about centroid (instead of just edges about centroid)
 * - [2a6x] 2x2 (instead of 3x3) contrast determination kernel is now an option (provides thinner lines of contrast and so much better for centred feature detection without quad fit) , and so interpixel contrast maps can be generated using pixel rgb maps, although currently assuming pixel depth maps, in the future consider in 3DOD supporting interpixel depth maps - these may be common for parallax generated depth information.
 *			check; error: discontinous edge
 * 			check; error - boundary edge false identification
 *			check error; numberOfPossibleCrawlPaths == 0
 * - [2a7x] MySQL Database introduction
 * - [2a8x] MySQL Database Geometric bin/index introduction + Avg col bin/index introduction + JPEG DCT bin/index introduction + ORmain.cpp front end introduction [2a8i] +
 * - [2a9x] [Re] compile and test in Windows using MS Visual Studio
 * - [2a10x] minor patches
 * - [2b] Decision Tree realtime software comparator
 * - [2c] pixmaps (Alltext) stored in MySQL database
 * - [2d] integrate ORrules.xml paramters file
 * - [2e] outputs best match object results
 * - [2f] [Re] compile and test in Windows using MS Visual Studio (make installation procedure compatible with both GNU and commercial licenses)
 * - [2g] Preparation for PHP GUI; multiview support, workingfolder, etc
 * - [2h] SQL comparison Linear Combination Network (instead of DCT tree)
 *
 * Usage Examples;
 *
 * ./OR.exe -sqlipaddress localhost -sqlusername rich -sqlpassword Esteban7 -trainortest 1 -object house2DOD -cleartrain -multview multViewList2DOD.txt -tempfolder "/home/rich/baior/temp" -exefolder "/home/rich/baior/bin" -workingfolder "/home/rich/source/source"
 *
 * ./OR.exe -sqlipaddress localhost -sqlusername rich -sqlpassword Esteban7 -trainortest 1 -object house2DOD -imageext .png -width 768 -height 576 -cleartrain -tempfolder "/home/rich/baior/temp" -exefolder "/home/rich/baior/bin" -workingfolder "/home/rich/source/source"
 * ./OR.exe -sqlipaddress localhost -sqlusername rich -sqlpassword Esteban7 -trainortest 0 -object house2DOD -imageext .png -width 768 -height 576 -view 1 -tempfolder "/home/rich/baior/temp" -exefolder "/home/rich/baior/bin" -workingfolder "/home/rich/source/source"
 *
 *
 * ./OR.exe -sqlipaddress localhost -sqlusername rich -sqlpassword Esteban7 -trainortest 1 -object house3DOD -od3 -cleartrain -multview multViewList3DOD.txt -tempfolder "/home/rich/baior/temp" -exefolder "/home/rich/baior/bin" -workingfolder "/home/rich/source/source"
 *
 * ./OR.exe -sqlipaddress localhost -sqlusername rich -sqlpassword Esteban7 -trainortest 1 -object house3DOD -imageext .png -width 400 -height 400 -od3 -depthext .depth.png -cleartrain -tempfolder "/home/rich/baior/temp" -exefolder "/home/rich/baior/bin" -workingfolder "/home/rich/source/source"
 * ./OR.exe -sqlipaddress localhost -sqlusername rich -sqlpassword Esteban7 -trainortest 0 -object house3DOD -imageext .png -width 400 -height 400 -od3 -depthext .depth.png -view 1 -tempfolder "/home/rich/baior/temp" -exefolder "/home/rich/baior/bin" -workingfolder "/home/rich/source/source"
 *
 *
 * Future Developments;
 *	- since in snapshots, num polygons approaches and even exceeds num pixels - we should consider a raytracer instead of using opengl
 *	- 3DOD surface mesh feature detection
 *	- 3DOD test and debug combined mesh feature detection
 *
 *******************************************************************************/

#ifndef HEADER_SHARED_GLOBAL_DEFS
#define HEADER_SHARED_GLOBAL_DEFS

	//required for string and atof
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <time.h>
	#include <math.h>
	using namespace std;


	/**********
	OS DEPENDENT VARIABLES;
	***********/

#define LINUX
#ifndef LINUX
	//else assume windows (affects default parts directory only - this is ISO C++ so it should compile on any platform)
	//#include <windows.h>
#endif


	/**********
	SOURCE PROJECT VARIABLES;
	***********/

	//current/active tests;
//#define COMPILE_OR		//or.exe
//#define COMPILE_GIA
//#define COMPILE_GIA_WITH_CE
//#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN	//ORTHimageCategorisationNN.exe
//#define COMPILE_CS		//cs.exe
//#define COMPILE_RT		//rt.exe
//#define COMPILE_ANN_WITH_RT	//ann.exe
//#define COMPILE_ANN		//ann.exe
#define COMPILE_LRRC
//#define COMPILE_OLC

//inactive tests;
//#define COMPILE_LRRC_WITH_ANN		[compilation broken; requires updating]
//#define COMPILE_TH_ANN_WITH_LRRC	[compilation broken; requires updating]


	//old tests
//#define COMPILE_TH_OR_METHOD_2DOD
//#define COMPILE_TH_OR_METHOD_3DOD
//#define COMPILE_TH_RT
//#define COMPILE_TH_OR_METHOD_2DOD_WITH_ANN
//#define COMPILE_TH_OR_METHOD_3DOD_WITH_ANN


#ifdef COMPILE_GIA_WITH_CE
	#define COMPILE_GIA
	#define USE_CE
#endif
#ifdef COMPILE_GIA
	#define USE_RT
	#define USE_GIA
#endif


//#define DEBUG_TH_ANN_USE_ORIGINAL_RANDOMISATION	NB there appears to be a bug in the original bias/weight randomisation process
#ifdef COMPILE_TH_OR_IMAGE_CATEGORISTION_NN

	//#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN_USE_MULTI_BIT_OUTPUT_PER_NET
	#ifdef COMPILE_TH_OR_IMAGE_CATEGORISTION_NN_USE_MULTI_BIT_OUTPUT_PER_NET
		#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN_USE_MULTI_BIT_OUTPUT_PER_NET_OUTPUTS (4)
		#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN_USE_MULTI_BIT_OUTPUT_PER_NET_NUM_BITS (6)
	#else
		#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN_USE_MULTI_BIT_OUTPUT_PER_NET_OUTPUTS (2)
		#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN_USE_MULTI_BIT_OUTPUT_PER_NET_NUM_BITS (1)
	#endif

	/*
	DEBUG_TH_OR_IMAGE_CATEGORISTION_NN debug;
	*/
	#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN		//temp - reduces number of neural nets used
	//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_3
	//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_2
	//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_4
	//#define OR_IMAGE_CATEGORISTION_NN_USE_SMALL_IMAGES


	//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_USE_LINEAR_COMBINATION_NETWORK	//use very simple neuron function (not exponential)
	#ifdef DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_USE_LINEAR_COMBINATION_NETWORK
		//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_DO_NOT_USE_NEGATIVE_BIASES_AND_WEIGHTS
	#else
		//#define TH_OR_IMAGE_CATEGORISTION_NN_USE_HEAVY_RANDOMISATION_OF_BIASES_AND_WEIGHTS
		#ifdef TH_OR_IMAGE_CATEGORISTION_NN_USE_HEAVY_RANDOMISATION_OF_BIASES_AND_WEIGHTS
			//#define TH_OR_IMAGE_CATEGORISTION_NN_USE_HEAVY_RANDOMISATION_OF_BIASES_AND_WEIGHTS_DEMONSTRATION
			#ifdef TH_OR_IMAGE_CATEGORISTION_NN_USE_HEAVY_RANDOMISATION_OF_BIASES_AND_WEIGHTS_DEMONSTRATION
				//#define OR_IMAGE_CATEGORISTION_NN_USE_SMALL_IMAGES	//used to demostrate heavy randomisation actually working
				#define DEBUG_TH_ANN_USE_ORIGINAL_RANDOMISATION		//used to demostrate heavy randomisation actually working
			#endif
			#define TH_OR_IMAGE_CATEGORISTION_NN_USE_HEAVY_RANDOMISATION_OF_BIASES_AND_WEIGHTS_BIAS_MULT (2.0)	//-2.0 -> +2.0
			#define TH_OR_IMAGE_CATEGORISTION_NN_USE_HEAVY_RANDOMISATION_OF_BIASES_AND_WEIGHTS_WEIGHT_MULT (4.0)	//-2.0 -> +2.0
				//temp;
			//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_DO_NOT_RANDOMISE_BIASES
			//#define DEBUG_TH_OR_IMAGE_CATEGORISTION_NN_DO_NOT_RANDOMISE_WEIGHTS
		#endif
	#endif

	/*
	IF_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D... improvements for image processing [local comparisons to combat anti-aliasing];
	*/
#endif

#define IF_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D_RADIALBIAS_USE_NEARBY_POINTS_INSTEAD
#ifdef IF_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D_RADIALBIAS_USE_NEARBY_POINTS_INSTEAD
	#ifdef OR_IMAGE_CATEGORISTION_NN_USE_SMALL_IMAGES
		#define IF_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D_RADIALBIAS_BIAS (2.0)
	#else
		#define IF_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D_RADIALBIAS_BIAS (4.0)	//4.0
	#endif
#else
	#define IF_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D_RADIALBIAS_BIAS (1.0)
#endif
#define LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_SQUARE2D_USE_CENTRED



//#define OR_IMAGE_COMPARISON_SQL_LINEAR_COMBINATION_NETWORK
#define OR_IMAGE_COMPARISON_SQL_LINEAR_COMBINATION_NETWORK_MAX_DIFF "10000000000000.0"	//100000
#define OR_IMAGE_COMPARISON_SQL_LINEAR_COMBINATION_NETWORK_DOUBLE_TO_U_LONG_CONVERSION (1e6)

//#define DEBUG_OR_PRINT_OR_RULES_EXTERN_VARS

#define USE_OLD_ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST

//#define OR_METHOD3DOD_IF_NOT_USING_MESH_LISTS_USE_CENTRED_FEATURE_DETECTION_DURING_ZOOM		//not yet tested
//#define OR_METHOD2DOD_IF_NOT_USING_MESH_LISTS_USE_CENTRED_FEATURE_DETECTION_DURING_ZOOM		//this seems to lower performance
//#define OR_DEBUG_METHOD_ASSUME_TRAIN_AND_TEST_WITH_SINGLE_VIEWPOINT		//currently being retested with/without
//#define OR_DEBUG_COMPARISON_ALLOW_SAME_OBJECT_AND_SAME_VIEW_TO_BE_COMPARED
#define OR_DEBUG_COMPARISON_ALLOW_SAME_OBJECT_BUT_DIFFERENT_VIEWS_TO_BE_COMPARED




	/**********
	OR HIGH LEVEL OPTIMISATION VARIABLES AVAILABLE IN ORrules.xml;
	***********/

#define EXE_FOLDER_PATH_MAX_LENGTH (1000)
extern char * exeFolderCharStar;
extern char * workingFolderCharStar;
extern char * tempFolderCharStar;

//OR_IMAGE_COMPARISON_DECISION_TREE...

extern bool OR_IMAGE_COMPARISON_DECISION_TREE;

extern bool OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING;
extern bool OR_IMAGE_COMPARISON_DECISION_TREE_AVERAGE_RGB_DEV_BINNING;
extern bool OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING;
extern bool OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON;

extern bool OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING;
extern bool OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING;
extern bool OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING;
extern bool OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON;

extern bool OR_IMAGE_COMPARISON_GEOMETRIC_COMPARISON_BINNING;
extern bool OR_IMAGE_COMPARISON_AVERAGE_RGB_DEV_BINNING;
extern bool OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING;
extern bool OR_IMAGE_COMPARISON_SMALL_HUE_DEV_MAP_COMPARISON;

extern bool OR_IMAGE_COMPARISON_TEST_GEO_BIN_ACCURACY;

#define OR_IMAGE_COMPARISON_DECISION_TREE_NAME "OR_IMAGE_COMPARISON_DECISION_TREE"

#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_NAME "OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING"
#define OR_IMAGE_COMPARISON_DECISION_TREE_AVERAGE_RGB_DEV_BINNING_NAME "OR_IMAGE_COMPARISON_DECISION_TREE_AVERAGE_RGB_DEV_BINNING"
#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NAME "OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING"
#define OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON_NAME "OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON"

#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NAME "OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING"
#define OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING_NAME "OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING"
#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NAME "OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING"
#define OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON_NAME "OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON"

extern bool OR_IMAGE_COMPARISON_SQL_GET_TEST_DATA_FROM_SQL;		//tested - default ON [this should be able to be turned off for optimisation purposes, it needs to fix up memory leak however] - this will not be changable in xml file, it should never need to be changed in release versions
extern bool OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE;		//tested - default ON [turn this off to display html results file properly] - this will not be changable in xml file, it should never need to be changed in release versions

#define OR_IMAGE_COMPARISON_SQL_GET_TEST_DATA_FROM_SQL_NAME "OR_IMAGE_COMPARISON_SQL_GET_TEST_DATA_FROM_SQL"					//tested - default ON [this should be able to be turned off for optimisation purposes, it needs to fix up memory leak however] - this will not be changable in xml file, it should never need to be changed in release versions
#define OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE_NAME "OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE"					//tested - default ON [turn this off to display html results file properly] - this will not be changable in xml file, it should never need to be changed in release versions


/*
#ifdef OR_IMAGE_COMPARISON_SQL

	//ORmethod.h and ORcomparison.h;
	//#define OR_IMAGE_COMPARISON_DECISION_TREE
	#ifdef OR_IMAGE_COMPARISON_DECISION_TREE
		#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING			//tested - default ON
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_AVERAGE_RGB_DEV_BINNING			//not tested - default OFF
		#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING	//tested - default ON
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON		//not tested -  default OFF - kind of works but not enough successful comparisons
		#define OR_IMAGE_COMPARISON_DECISION_TREE_SLOW_TO_TRAIN_REQUIRES_HIGH_MEM_BUT_HIGH_REDUNDANCY
	#else
		#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING				//tested - default ON
		//#define OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING				//not tested - default OFF
		#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING		//tested - default ON
		//#define OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON				//not tested - default OFF
	#endif

	#define OR_IMAGE_COMPARISON_SQL_GET_TEST_DATA_FROM_SQL						//tested - default ON [this should be able to be turned off for optimisation purposes, it needs to fix up memory leak however] - this will not be changable in xml file, it should never need to be changed in release versions
	#define OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE					//tested - default ON [turn this off to display html results file properly] - this will not be changable in xml file, it should never need to be changed in release versions

#endif
*/


//OR_METHOD_GEOMETRIC_COMPARISON...

extern bool OR_METHOD_TRANSFORM_NEARBY_FEATURES;

extern bool OR_SQL_DATABASE_STORE_ALL_NEARBY_AND_OT_FEATURES;

extern bool OR_METHOD_TRANSFORM_KEY_OT_FEATURES;
extern bool OR_METHOD_TRANSFORM_ALL_FEATURES;
extern bool OR_METHOD_CREATE_OT_FEATURES_FILE;
extern bool OR_METHOD_CREATE_ALL_FEATURES_FILE;

extern bool OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TEST_FILE_IO;
extern bool OR_METHOD_CREATE_NEARBY_FEATURES_FILE;
extern bool OR_METHOD_CREATE_NEARBY_FEATURES_FILE_ALWAYS;
extern bool OR_METHOD_CREATE_NEARBY_FEATURES_FILE_DURING_TEST;




//OR_FEATURES... (including Mesh Lists and Feature Detection using contiguous regions);

//xml determined by default;
extern bool OR_USE_FIND_CORNER_FEATURES;
extern bool OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES;
extern bool OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES;
extern bool OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY;

extern bool OR_METHOD_USE_MESH_LISTS;	//[has not been tested with centred feature detection]
extern bool OR_METHOD_3DOD_USE_MESH_LISTS_COMBINED;
extern double OR_METHOD_3DOD_USE_ADVANCED_INTERP_MESH_JOINING_MAXIMUM_RECONCILIATION_DISTANCE;
extern bool OR_METHOD_2DOD_USE_MESH_LISTS_COMBINED;	//never use this - not yet implemented

//dynamically determined by default;
extern bool OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP;
extern bool OR_METHOD2DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP;
extern bool OR_METHOD_QUADRATIC_FIT_FOR_MESH_LISTS_HAS_BEEN_PROGRAMMED;
extern bool OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_BOOL;
extern bool OR_METHOD2DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_BOOL;
extern bool OR_TRACE_CONTIGUOUS_REGION_BOUNDARY_DIAGONALS;
extern bool OR_TRACE_CONTIGUOUS_REGION_BOUNDARY_RESET_EDGES_DYNAMICALLY_OPT;
extern bool OR_METHOD3DOD_USE_3D_EDGE_POINTS_CALCULATED_DURING_QUADRATIC_FIT_INSTEAD_OF_DURING_EDGE_TRACE;
extern bool OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_TRACE_MIN_MAX_NOT_TESTED_YET;
extern bool OR_CREATE_INTERPOLATED_MESH_REFERENCE_LIST_USING_MESH_LIST;

#define OR_USE_FIND_CORNER_FEATURES_NAME "OR_USE_FIND_CORNER_FEATURES"
#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_NAME "OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES"
#define OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_NAME "OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES"
#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY_NAME "OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY"

#define OR_METHOD_USE_MESH_LISTS_NAME "OR_METHOD_USE_MESH_LISTS"
#define OR_METHOD_3DOD_USE_MESH_LISTS_COMBINED_NAME "OR_METHOD_3DOD_USE_MESH_LISTS_COMBINED"
#define OR_METHOD_3DOD_USE_ADVANCED_INTERP_MESH_JOINING_MAXIMUM_RECONCILIATION_DISTANCE_NAME "OR_METHOD_3DOD_USE_ADVANCED_INTERP_MESH_JOINING_MAXIMUM_RECONCILIATION_DISTANCE"
#define OR_METHOD_2DOD_USE_MESH_LISTS_COMBINED_NAME "OR_METHOD_2DOD_USE_MESH_LISTS_COMBINED"	//never use this - not yet implemented

//dynamically determined by default
#define OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_NAME "OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP"
#define OR_METHOD2DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_NAME "OR_METHOD2DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP"
#define OR_METHOD_QUADRATIC_FIT_FOR_MESH_LISTS_HAS_BEEN_PROGRAMMED_NAME "OR_METHOD_QUADRATIC_FIT_FOR_MESH_LISTS_HAS_BEEN_PROGRAMMED"
#define OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_BOOL_NAME "OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_BOOL"
#define OR_METHOD2DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_BOOL_NAME "OR_METHOD2DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP_BOOL"
#define OR_TRACE_CONTIGUOUS_REGION_BOUNDARY_DIAGONALS_NAME "OR_TRACE_CONTIGUOUS_REGION_BOUNDARY_DIAGONALS"
#define OR_TRACE_CONTIGUOUS_REGION_BOUNDARY_RESET_EDGES_DYNAMICALLY_OPT_NAME "OR_TRACE_CONTIGUOUS_REGION_BOUNDARY_RESET_EDGES_DYNAMICALLY_OPT"
#define OR_METHOD3DOD_USE_3D_EDGE_POINTS_CALCULATED_DURING_QUADRATIC_FIT_INSTEAD_OF_DURING_EDGE_TRACE_NAME "OR_METHOD3DOD_USE_3D_EDGE_POINTS_CALCULATED_DURING_QUADRATIC_FIT_INSTEAD_OF_DURING_EDGE_TRACE"
#define OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_TRACE_MIN_MAX_NOT_TESTED_YET_NAME "OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_TRACE_MIN_MAX_NOT_TESTED_YET"
#define OR_CREATE_INTERPOLATED_MESH_REFERENCE_LIST_USING_MESH_LIST_NAME "OR_CREATE_INTERPOLATED_MESH_REFERENCE_LIST_USING_MESH_LIST"

#define OR_METHOD_2DOD_USE_ADVANCED_INTERP_MESH_JOINING_MAXIMUM_RECONCILIATION_DISTANCE (0.5)	//half pixel



//#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY_EXTRA_NOT_NECESSARY_AND_BUGGY	//untested - doesnt work needs fixing
//#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY_EXTRA_NOT_NECESSARY_AND_BUGGY_2	//untested - doesnt work needs fixing

/*
//ORfeature.h;
#define OR_USE_FIND_CORNER_FEATURES												//tested - default ON	//works for both objects with corners only [heitger feature detection]
#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES										//tested - default ON	//works for both objects with and without corners
#ifndef OR_USE_FIND_CORNER_FEATURES
	#define OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES						//tested - default OFF	//works for both objects with and without corners (should not be used in conjunction with OR_USE_FIND_CORNER_FEATURES)
	#ifdef OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES
		//#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY					//tested - default OFF	//only useful if boundary features are being detected [increases accuracy, lowers numbers of features]
		//#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY_EXTRA_NOT_NECESSARY_AND_BUGGY	//untested - doesnt work needs fixing
		//#define OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY_EXTRA_NOT_NECESSARY_AND_BUGGY_2	//untested - doesnt work needs fixing
		//#define OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_DO_NOT_USE_UNCHANGING_CASE		//tested - default OFF
	#endif
#endif

#ifdef TRY_UNTESTED_SOFTWARE2
	#define OR_METHOD_3DOD_USE_MESH_LISTS_COMBINED	//probably need to verify quadratic fit edges are calculated properly upon mesh advanced join
	#define OR_METHOD_3DOD_USE_ADVANCED_INTERP_MESH_JOINING_MAXIMUM_RECONCILIATION_DISTANCE (0.1) //this needs to be made dynamic based upon vi
	//#define OR_METHOD_2DOD_USE_MESH_LISTS_COMBINED		//dont use	//not yet implemented (low priority) - there is no way of combining 2D mesh lists without eg x/y offset information...
#endif
*/



extern double MIN_REGION_SIZE_TO_CALCULATE_CENTRED_FEATURE;					//this needs to be made dynamic based upon vi
extern int MINIMUM_NUMBER_OF_PIXELS_IN_A_BOUNDARY;
extern bool OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_DO_NOT_USE_UNCHANGING_CASE;		//tested - default OFF
extern double OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE;						//this needs to be made dynamic based upon vi
extern double OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE_2;	//this needs to be made dynamic based upon vi 		//this needs to be checked, this value might need to be increased slightly
extern double OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_POINT_MOVEMENT;				//this needs to be made dynamic based upon vi
extern double OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE;						//this needs to be made dynamic based upon zoom??
extern double OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE_2;	//this needs to be made dynamic based upon zoom??	//this needs to be checked, this value might need to be increased slightly

#define MIN_REGION_SIZE_TO_CALCULATE_CENTRED_FEATURE_NAME "MIN_REGION_SIZE_TO_CALCULATE_CENTRED_FEATURE"	//this needs to be made dynamic based upon vi
#define MINIMUM_NUMBER_OF_PIXELS_IN_A_BOUNDARY_NAME "MINIMUM_NUMBER_OF_PIXELS_IN_A_BOUNDARY"
#define OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_DO_NOT_USE_UNCHANGING_CASE_NAME "OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_DO_NOT_USE_UNCHANGING_CASE"		//tested - default OFF
#define OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE_NAME "OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE"						//this needs to be made dynamic based upon vi
#define OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE_2_NAME "OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE_2"	//this needs to be made dynamic based upon vi //this needs to be checked, this value might need to be increased slightly
#define OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_POINT_MOVEMENT_NAME "OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_POINT_MOVEMENT"					//this needs to be made dynamic based upon vi
#define OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE_NAME "OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE"						//this needs to be made dynamic based upon zoom??
#define OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE_2_NAME "OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE_2"	//this needs to be made dynamic based upon zoom??	//this needs to be checked, this value might need to be increased slightly


//#define OR_USE_FOREGROUND_DEPTH_CHECKS_OLD
#define OR_USE_FOREGROUND_DEPTH_CHECKS

//#define NEWCHECKTHIS
#define NEWCHECKTHIS2
#define OR_QUADRATIC_FIT_EDGE_RELAXED_REQ
#define OR_QUADRATIC_FIT_EDGE_RELAXED_REQ_2


/*
#define MIN_REGION_SIZE_TO_CALCULATE_CENTRED_FEATURE (20)	//this needs to be made dynamic based upon vi
#define MINIMUM_NUMBER_OF_PIXELS_IN_A_BOUNDARY (2)
//#define OR_USE_FIND_CONTIGUOUS_REGION_CENTRED_FEATURES_BOUNDARY_FEATURES_DO_NOT_USE_UNCHANGING_CASE		//tested - default OFF
#define OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE (0.1)						//this needs to be made dynamic based upon vi
#define OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE_2 (OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_NOISE)	//this needs to be made dynamic based upon vi //this needs to be checked, this value might need to be increased slightly
#define OR_METHOD_3DOD_CONTINUOUS_EDGE_MAX_POINT_MOVEMENT (0.3)					//this needs to be made dynamic based upon vi
#define OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE (1.0)						//this needs to be made dynamic based upon zoom??
#define OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE_2 (OR_METHOD_2DOD_CONTINUOUS_EDGE_MAX_NOISE)	//this needs to be made dynamic based upon zoom??	//this needs to be checked, this value might need to be increased slightly
*/



//OR_METHOD3DOD FEATURE...

extern bool OR_METHOD3DOD_USE_MESH_NORMAL_AND_NORMAL_CONTRAST;
extern bool OR_METHOD3DOD_USE_SHAPE_CONTRAST_INSTEAD_OF_LUMINOSITY_CONTRAST_FOR_FEATURE_DETECTION;
extern bool OR_METHOD3DOD_USE_NORMAL_CONTRAST_INSTEAD_OF_DEPTH_GRADIENT_AND_DEPTH_GRADIENT_CONTRAST_FOR_SHAPE_CONTRAST;

#define OR_METHOD3DOD_USE_MESH_NORMAL_AND_NORMAL_CONTRAST_NAME "OR_METHOD3DOD_USE_MESH_NORMAL_AND_NORMAL_CONTRAST"
#define OR_METHOD3DOD_USE_SHAPE_CONTRAST_INSTEAD_OF_LUMINOSITY_CONTRAST_FOR_FEATURE_DETECTION_NAME "OR_METHOD3DOD_USE_SHAPE_CONTRAST_INSTEAD_OF_LUMINOSITY_CONTRAST_FOR_FEATURE_DETECTION"
#define OR_METHOD3DOD_USE_NORMAL_CONTRAST_INSTEAD_OF_DEPTH_GRADIENT_AND_DEPTH_GRADIENT_CONTRAST_FOR_SHAPE_CONTRAST_NAME "OR_METHOD3DOD_USE_NORMAL_CONTRAST_INSTEAD_OF_DEPTH_GRADIENT_AND_DEPTH_GRADIENT_CONTRAST_FOR_SHAPE_CONTRAST"

#define OR_METHOD_3DOD_USE_DYNAMIC_WORLD_COORD_DETERMINATION_USING_DEPTH
/*
#define OR_METHOD3DOD_USE_MESH_NORMAL_AND_NORMAL_CONTRAST
//#define OR_METHOD3DOD_USE_SHAPE_CONTRAST_INSTEAD_OF_LUMINOSITY_CONTRAST_FOR_FEATURE_DETECTION
#ifdef OR_METHOD3DOD_USE_SHAPE_CONTRAST_INSTEAD_OF_LUMINOSITY_CONTRAST_FOR_FEATURE_DETECTION
	#define OR_METHOD3DOD_USE_NORMAL_CONTRAST_INSTEAD_OF_DEPTH_GRADIENT_AND_DEPTH_GRADIENT_CONTRAST_FOR_SHAPE_CONTRAST	//this is an update which gets rid of depth gradient contrast and depth contrast maps
#endif
*/

extern double OR_METHOD_3DOD_DEPTH_MAP_TO_IMAGE_CONVERSION_SCALE;

#define OR_METHOD_3DOD_DEPTH_MAP_TO_IMAGE_CONVERSION_SCALE_NAME "OR_METHOD_3DOD_DEPTH_MAP_TO_IMAGE_CONVERSION_SCALE"

/*
#define OR_METHOD_3DOD_DEPTH_MAP_TO_IMAGE_CONVERSION_SCALE (0.001)
*/





//OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING...

extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DISTINCT_VALS_PER_COL;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS_IN_BITS;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY;			//deterministic dct coeff comparison requirement
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_CHROMA_ENHANCED; 	//deterministic dct coeff comparison requirement

extern char OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_STRING[];			//deterministic dct coeff comparison requirement
extern char OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_CHROMA_ENHANCED_STRING[]; 	//deterministic dct coeff comparison requirement

extern bool OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_COLOUR_INFORMATION;
extern bool OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_MATCHED_LUM_CHROMA_SUBSAMPLING;
extern bool OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_ENHANCED_CHROMA_SUBSAMPLING;

extern char OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_CHROMA_SUBSAMPLING_STRING[];

extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCr;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCb;

extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_0_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_0_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_1_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_1_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_2_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_2_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_3_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_3_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_4_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_4_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_5_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_5_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_6_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_6_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_7_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_7_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_8_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_8_Y;

extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_0_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_0_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_1_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_1_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_2_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_2_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_3_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_3_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_4_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_4_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_5_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_5_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_6_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_6_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_7_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_7_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_8_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_8_Y;

extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_0_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_0_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_1_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_1_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_2_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_2_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_3_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_3_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_4_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_4_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_5_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_5_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_6_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_6_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_7_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_7_Y;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_8_X;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_8_Y;

extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS_SIGNED_OFFSET;
extern int OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS;

#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DISTINCT_VALS_PER_COL_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DISTINCT_VALS_PER_COL"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS_IN_BITS_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINS_IN_BITS"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY"			//deterministic dct coeff comparison requirement
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_CHROMA_ENHANCED_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_CHROMA_ENHANCED" 	//deterministic dct coeff comparison requirement

#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_COLOUR_INFORMATION_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_COLOUR_INFORMATION"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_MATCHED_LUM_CHROMA_SUBSAMPLING_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_MATCHED_LUM_CHROMA_SUBSAMPLING"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_ENHANCED_CHROMA_SUBSAMPLING_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_USE_ENHANCED_CHROMA_SUBSAMPLING"

#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCr_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCr"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCb_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCb"

#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_0_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_0_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_0_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_0_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_1_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_1_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_1_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_1_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_2_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_2_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_2_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_2_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_3_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_3_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_3_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_3_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_4_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_4_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_4_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_4_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_5_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_5_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_5_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_5_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_6_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_6_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_6_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_6_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_7_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_7_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_7_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_7_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_8_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_8_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_8_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_Y_CELL_8_Y"

#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_0_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_0_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_0_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_0_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_1_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_1_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_1_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_1_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_2_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_2_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_2_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_2_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_3_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_3_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_3_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_3_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_4_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_4_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_4_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_4_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_5_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_5_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_5_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_5_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_6_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_6_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_6_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_6_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_7_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_7_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_7_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_7_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_8_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_8_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_8_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCR_CELL_8_Y"

#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_0_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_0_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_0_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_0_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_1_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_1_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_1_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_1_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_2_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_2_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_2_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_2_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_3_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_3_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_3_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_3_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_4_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_4_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_4_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_4_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_5_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_5_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_5_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_5_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_6_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_6_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_6_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_6_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_7_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_7_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_7_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_7_Y"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_8_X_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_8_X"
#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_8_Y_NAME "OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DCT_COEFF_SELECTION_ARRAY_YCB_CELL_8_Y"





//OR_SHARED_VARS...	//general contrast threshold constraints

#define RGB_RED (0)
#define RGB_GREEN (1)
#define RGB_BLUE (2)
#define RGB_NUM (3)

#define MAX_RGB_VAL (255)
#define MAX_LUMINOSITY (MAX_RGB_VAL*RGB_NUM)
#define MAX_NORMAL (1.0)

extern bool OR_USE_CONTRAST_CALC_METHOD_C;		//OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY may be more recommended with OR_USE_CONTRAST_CALC_METHOD_B
extern bool OR_USE_CONTRAST_CALC_METHOD_B;		//OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY may be more recommended with OR_USE_CONTRAST_CALC_METHOD_B

extern double LUMINOSITY_CONTRAST_FRACTION_THRESHOLD;
extern double DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD;	//this needs to be dynamic - not static - and should be dependant upon focal length
extern double DEPTH_CONTRAST_FRACTION_THRESHOLD;		//this needs to be dynamic - not static - and should be dependant upon focal length
extern double POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD;

extern double LUMINOSITY_FRACTION_THRESHOLD;
extern double OR_MAX_DEPTH_NOISE;
extern double ESTIMATE_MAX_DEPTH_T_REAL;

extern double MAX_LUMINOSITY_CONTRAST;
extern double MAX_NORMAL_CONTRAST;
extern double ESTIMATE_MAX_DEPTH_CONTRAST;
extern double ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST;

extern double EDGE_LUMINOSITY_CONTRAST_THRESHOLD;
extern double EDGE_LUMINOSITY_THRESHOLD;
extern double EDGE_NORMAL_CONTRAST_THRESHOLD;
extern double EDGE_DEPTH_CONTRAST_THRESHOLD;
extern double EDGE_DEPTH_GRADIENT_CONTRAST_THRESHOLD;

extern int INTERPIXEL_CONTRAST_MAP_TYPE_RGB_LUMINOSITY_DEPTH_OR_POINT;
extern int INTERPIXEL_CONTRAST_MAP_TYPE_LUMINOSITY_OR_DEPTH_CONTRAST;
extern int INTERPIXEL_CONTRAST_MAP_TYPE_NORMAL_OR_GRADIENT_CONTRAST;

#define OR_USE_CONTRAST_CALC_METHOD_C_NAME "OR_USE_CONTRAST_CALC_METHOD_C"
#define OR_USE_CONTRAST_CALC_METHOD_B_NAME "OR_USE_CONTRAST_CALC_METHOD_B"

#define LUMINOSITY_CONTRAST_FRACTION_THRESHOLD_NAME "LUMINOSITY_CONTRAST_FRACTION_THRESHOLD"
#define DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD_NAME "DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD"		//this needs to be dynamic - not static - and should be dependant upon focal length
#define DEPTH_CONTRAST_FRACTION_THRESHOLD_NAME "DEPTH_CONTRAST_FRACTION_THRESHOLD"				//this needs to be dynamic - not static - and should be dependant upon focal length
#define POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD_NAME "POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD"

#define LUMINOSITY_FRACTION_THRESHOLD_NAME "LUMINOSITY_FRACTION_THRESHOLD"
#define OR_MAX_DEPTH_NOISE_NAME "OR_MAX_DEPTH_NOISE"
#define ESTIMATE_MAX_DEPTH_T_REAL_NAME "ESTIMATE_MAX_DEPTH_T_REAL"



/*
//SHAREDvars.h; general contrast threshold constraints
#define OR_USE_CONTRAST_CALC_METHOD_C								//tested - default ON
#ifndef OR_USE_CONTRAST_CALC_METHOD_C
	#define OR_USE_CONTRAST_CALC_METHOD_B							//tested - default OFF
#endif
#ifdef OR_USE_CONTRAST_CALC_METHOD_B
	#define LUMINOSITY_CONTRAST_FRACTION_THRESHOLD (0.02)
	#define DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD (0.02)	//this needs to be dynamic - not static - and should be dependant upon focal length
	#define DEPTH_CONTRAST_FRACTION_THRESHOLD (0.02)		//this needs to be dynamic - not static - and should be dependant upon focal length
	#define POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD (0.02)
#elif defined OR_USE_CONTRAST_CALC_METHOD_C
	#define LUMINOSITY_CONTRAST_FRACTION_THRESHOLD (0.05)
	#define DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD (0.05)	//this needs to be dynamic - not static - and should be dependant upon focal length
	#define DEPTH_CONTRAST_FRACTION_THRESHOLD (0.05)		//this needs to be dynamic - not static - and should be dependant upon focal length
	#define POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD (0.1)
#else
	#define LUMINOSITY_CONTRAST_FRACTION_THRESHOLD (0.05)
	#define DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD (0.05)	//this needs to be dynamic - not static - and should be dependant upon focal length
	#define DEPTH_CONTRAST_FRACTION_THRESHOLD (0.05)		//this needs to be dynamic - not static - and should be dependant upon focal length
	#define POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD (0.1)
#endif
#define LUMINOSITY_FRACTION_THRESHOLD (0.01)
#define OR_MAX_DEPTH_NOISE (0.1)
#define ESTIMATE_MAX_DEPTH_T_REAL (20.0)	//20.0

#define MAX_RGB_VAL (255)
#define MAX_LUMINOSITY (MAX_RGB_VAL*RGB_NUM)
#define MAX_NORMAL (1.0)
#ifdef OR_USE_CONTRAST_CALC_METHOD_C
	#define MAX_LUMINOSITY_CONTRAST (MAX_LUMINOSITY*4)
	#define MAX_NORMAL_CONTRAST (MAX_NORMAL*3.0*4)
	#define ESTIMATE_MAX_DEPTH_CONTRAST (ESTIMATE_MAX_DEPTH_T_REAL)
	#define ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST (ESTIMATE_MAX_DEPTH_CONTRAST*4.0)
#elif defined OR_USE_CONTRAST_CALC_METHOD_B
	#define MAX_LUMINOSITY_CONTRAST (MAX_LUMINOSITY*8)
	#define MAX_NORMAL_CONTRAST (MAX_NORMAL*3.0*8)
	#define ESTIMATE_MAX_DEPTH_CONTRAST (ESTIMATE_MAX_DEPTH_T_REAL*8.0)
	#define ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST (ESTIMATE_MAX_DEPTH_CONTRAST*8.0*2.0)
#else
	#define MAX_LUMINOSITY_CONTRAST (MAX_LUMINOSITY)
	#define MAX_NORMAL_CONTRAST (MAX_NORMAL*3.0)
	#define ESTIMATE_MAX_DEPTH_CONTRAST (ESTIMATE_MAX_DEPTH_T_REAL)
	#define ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST (ESTIMATE_MAX_DEPTH_CONTRAST*2.0)
#endif

#define EDGE_LUMINOSITY_CONTRAST_THRESHOLD (MAX_LUMINOSITY_CONTRAST*LUMINOSITY_CONTRAST_FRACTION_THRESHOLD) 	//OLD = ~0.07*MAX_LUMINOSITY_CONTRAST = ~ ((20.0/254.0)*MAX_LUMINOSITY_CONTRAST)
#define EDGE_LUMINOSITY_THRESHOLD (MAX_LUMINOSITY*LUMINOSITY_FRACTION_THRESHOLD)
#define EDGE_NORMAL_CONTRAST_THRESHOLD (MAX_NORMAL_CONTRAST*POINT_NORMAL_CONTRAST_FRACTION_THRESHOLD)
#define EDGE_DEPTH_CONTRAST_THRESHOLD (ESTIMATE_MAX_DEPTH_CONTRAST*DEPTH_CONTRAST_FRACTION_THRESHOLD)
#define EDGE_DEPTH_GRADIENT_CONTRAST_THRESHOLD (ESTIMATE_MAX_DEPTH_CONTRAST*DEPTH_GRADIENT_CONTRAST_FRACTION_THRESHOLD)

#ifdef OR_USE_CONTRAST_CALC_METHOD_C
	#define INTERPIXEL_CONTRAST_MAP_TYPE_RGB_LUMINOSITY_DEPTH_OR_POINT (0)
	#define INTERPIXEL_CONTRAST_MAP_TYPE_LUMINOSITY_OR_DEPTH_CONTRAST (1)
	#define INTERPIXEL_CONTRAST_MAP_TYPE_NORMAL_OR_GRADIENT_CONTRAST (2)
#else
	#define INTERPIXEL_CONTRAST_MAP_TYPE_RGB_LUMINOSITY_DEPTH_OR_POINT (0)
	#define INTERPIXEL_CONTRAST_MAP_TYPE_LUMINOSITY_OR_DEPTH_CONTRAST (0)
	#define INTERPIXEL_CONTRAST_MAP_TYPE_NORMAL_OR_GRADIENT_CONTRAST (0)
#endif

*/




//OR_METHOD2DOD...

extern bool OR_IMAGE_COMPARISON_PATTERN_NEVER_CULL_SNAPSHOTS;
extern bool OR_METHOD_DO_NOT_CULL_SNAPSHOT;
extern bool OR_METHOD_DO_NOT_CULL_SNAPSHOT_EXTREME;

#define OR_IMAGE_COMPARISON_PATTERN_NEVER_CULL_SNAPSHOTS_NAME "OR_IMAGE_COMPARISON_PATTERN_NEVER_CULL_SNAPSHOTS"
#define OR_METHOD_DO_NOT_CULL_SNAPSHOT_NAME "OR_METHOD_DO_NOT_CULL_SNAPSHOT"
#define OR_METHOD_DO_NOT_CULL_SNAPSHOT_EXTREME_NAME "OR_METHOD_DO_NOT_CULL_SNAPSHOT_EXTREME"

#define OR_METHOD2DOD_IMAGE_COMPARISON_CULL_ERROR (0.2)

/*
//ORmethod2DOD.h;
#define OR_IMAGE_COMPARISON_PATTERN_NEVER_CULL_SNAPSHOTS					//tested - default ON	//requires a very fast graphics card (and possibly CPU)
*/




//OR_METHOD...

extern bool OR_METHOD_SUPPORT_HIGH_LEVEL_SCALING;

extern bool OR_METHOD2DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS;
extern int OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS;
extern bool OR_METHOD3DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS ;
extern int OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS;

extern int OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TRAIN;
extern int OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TEST;
extern int OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TRAIN;
extern int OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TEST;

#define OR_METHOD_SUPPORT_HIGH_LEVEL_SCALING_NAME "OR_METHOD_SUPPORT_HIGH_LEVEL_SCALING"

#define OR_METHOD2DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS_NAME "OR_METHOD2DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS"
#define OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS_NAME "OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS"
#define OR_METHOD3DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS_NAME "OR_METHOD3DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS"
#define OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS_NAME "OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS"

#define OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TRAIN_NAME "OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TRAIN"
#define OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TEST_NAME "OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TEST"
#define OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TRAIN_NAME "OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TRAIN"
#define OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TEST_NAME "OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TEST"

/*
//ORmethod.h;

	//level of nearst feature detection redundancy;
#define OR_METHOD_ONLY_USE_ONE_POLY_PER_FEATURE_FAST_BUT_LOW_REDUNDANCY			//untested - default OFF
#define OR_METHOD_ONLY_USE_TWO_NEAREST_FEATURES_TO_COMPARE_FAST_BUT_LOW_REDUNDANCY		//untested - default OFF

#define OR_METHOD_SUPPORT_HIGH_LEVEL_SCALING							//tested - default ON

#ifdef OR_METHOD_SUPPORT_HIGH_LEVEL_SCALING
	#define OR_METHOD2DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS
	//#define OR_METHOD3DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS
	#ifdef OR_METHOD2DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS
		#define OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS (3)
	#else
		#define OR_METHOD2DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS (1)
	#endif
	#ifdef OR_METHOD3DOD_SUPPORT_SNAPSHOTS_AT_MULTIPLE_ZOOMS
		#define OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS (3)
	#else
		#define OR_METHOD3DOD_NUMBER_OF_SNAPSHOT_ZOOM_LEVELS (1)
	#endif
#endif

#define OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TRAIN (10000)		//old; 42
#define OR_METHOD3DOD_MAX_NUMBER_OF_POLYGONS_TEST (10000)		//old; 42
#define OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TRAIN (10000)		//old; 500
#define OR_METHOD2DOD_MAX_NUMBER_OF_POLYGONS_TEST (10000)		//old; 500
*/


//LD_OPENGL...

extern int OR_SNAPSHOT_WINDOW_POSITION_X;		//dependent upon resolution of monitor - should be moved to command line parameter
extern int OR_SNAPSHOT_WINDOW_POSITION_Y;	//dependent upon resolution of monitor - should be moved to command line parameter
#define OR_SNAPSHOT_WINDOW_POSITION_X_NAME "OR_SNAPSHOT_WINDOW_POSITION_X"	//dependent upon resolution of monitor - should be moved to command line parameter
#define OR_SNAPSHOT_WINDOW_POSITION_Y_NAME "OR_SNAPSHOT_WINDOW_POSITION_Y"	//dependent upon resolution of monitor - should be moved to command line parameter

//OR_IMAGE_COMPARISON...

extern double OR_IMAGE_COMPARISON_HAS_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION;				//not tested or used yet
extern double OR_IMAGE_COMPARISON_HAS_STARK_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION;			//not tested or used yet
extern double OR_IMAGE_COMPARISON_HAS_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION;		//5
extern double OR_IMAGE_COMPARISON_HAS_STARK_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION;
extern double IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR_BASE;
extern double IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR;
extern double OR_IMAGE_COMPARISON_STARK_LOCAL_DEVIATION_MIN_MIN_COL_DIFF;
extern double OR_IMAGE_COMPARISON_MAX_TOTAL_NUM_STARK_LOCAL_DEVIATIONS;			//need to change to (100.0/(28*28/2)) after testing
extern double OR_IMAGE_COMPARISON_STARK_LOCAL_CONTRAST_MIN_AVG_COL_DIFF;			//needs to be tested

#define OR_IMAGE_COMPARISON_HAS_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION_NAME "OR_IMAGE_COMPARISON_HAS_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION"				//not tested or used yet
#define OR_IMAGE_COMPARISON_HAS_STARK_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION_NAME "OR_IMAGE_COMPARISON_HAS_STARK_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION"			//not tested or used yet
#define OR_IMAGE_COMPARISON_HAS_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION_NAME "OR_IMAGE_COMPARISON_HAS_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION"		//5
#define OR_IMAGE_COMPARISON_HAS_STARK_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION_NAME "OR_IMAGE_COMPARISON_HAS_STARK_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION"
#define IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR_BASE_NAME "IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR_BASE"
#define OR_IMAGE_COMPARISON_STARK_LOCAL_DEVIATION_MIN_MIN_COL_DIFF_NAME "OR_IMAGE_COMPARISON_STARK_LOCAL_DEVIATION_MIN_MIN_COL_DIFF"
#define OR_IMAGE_COMPARISON_MAX_TOTAL_NUM_STARK_LOCAL_DEVIATIONS_NAME "OR_IMAGE_COMPARISON_MAX_TOTAL_NUM_STARK_LOCAL_DEVIATIONS"				//need to change to (100.0/(28*28/2)) after testing
#define OR_IMAGE_COMPARISON_STARK_LOCAL_CONTRAST_MIN_AVG_COL_DIFF_NAME "OR_IMAGE_COMPARISON_STARK_LOCAL_CONTRAST_MIN_AVG_COL_DIFF"				//needs to be tested


//#define OR_IMAGE_COMPARISON_MIN_TOTAL_NUM_STARK_LOCAL_CONTRASTS (100.0/(28*28/2))

//OR_OPERATIONS...

extern double XYCOORDINATES_CONVERSION_INTO_PIXELS;			//default 0.0002
extern double MAX_FEATURE_DISTANCE_ERROR_USING_DEPTH_MAP_METHOD;	//in pixel units
extern double MAX_FEATURE_DISTANCE_ERROR_USING_POINT_MAP_METHOD;	//in world units		//OLD;(0.001)

#define XYCOORDINATES_CONVERSION_INTO_PIXELS_NAME "XYCOORDINATES_CONVERSION_INTO_PIXELS"				//default 0.0002
#define MAX_FEATURE_DISTANCE_ERROR_USING_DEPTH_MAP_METHOD_NAME "MAX_FEATURE_DISTANCE_ERROR_USING_DEPTH_MAP_METHOD"	//in pixel units





//OR_PIXEL_MAPS...

extern double ESTIMATE_MAX_DEPTH_GRADIENT;
extern double ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST;
extern double DEPTH_GRADIENT_CONTRAST_THRESHOLD;

#define ESTIMATE_MAX_DEPTH_GRADIENT_NAME "ESTIMATE_MAX_DEPTH_GRADIENT"
#define ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST_NAME "ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST"
#define DEPTH_GRADIENT_CONTRAST_THRESHOLD_NAME "DEPTH_GRADIENT_CONTRAST_THRESHOLD"


extern bool DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_INTERPIXEL;
extern int DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH;
extern int DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT;

extern bool DEFAULT_NORMAL_MAP_GENERATION_INTERPIXEL;
extern int DEFAULT_NORMAL_MAP_GENERATION_KERNEL_WIDTH;
extern int DEFAULT_NORMAL_MAP_GENERATION_KERNEL_HEIGHT;


#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)

#define NORMAL_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define NORMAL_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define NORMAL_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define NORMAL_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)


//RT_PIXEL_MAPS...

extern bool DEFAULT_CONTRAST_MAP_GENERATION_INTERPIXEL;
extern int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH;
extern int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT;

#define CONTRAST_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define CONTRAST_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)





//OR_QUADRATIC_FIT...

extern double MAXIMUM_GRADIENT_OF_CURVATURE_WITH_RESPECT_TO_ORIENTATION_OF_CURVE;
extern double MAXIMUM_ALPHA_TO_BETA_GRADIENT_RATIO;
extern bool USE_EDGISE_3X3_KERNEL;
extern bool USE_EDGISE_5X5_KERNEL;
extern double A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_5X5_KERNEL; 				//(-EDGE_LUMINOSITY_CONTRAST_THRESHOLD/5)
extern double A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_3X3_KERNEL; 				//(-EDGE_LUMINOSITY_CONTRAST_THRESHOLD/5)
extern double HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD;							//NB this represents the optimised values for 2DOD, consider/test using (256*1.0) for 3DOD...!!
extern double HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD;							//NB this represents the optimised values for 2DOD, consider/test using (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/4.0) for 3DOD...!!
extern double HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD;

extern int QUADRATIC_FIT_KERNEL_SIZE;
extern double ZERO_CROSSING_POSITION_THRESHOLD;
extern double A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD;

#define MAXIMUM_GRADIENT_OF_CURVATURE_WITH_RESPECT_TO_ORIENTATION_OF_CURVE_NAME "MAXIMUM_GRADIENT_OF_CURVATURE_WITH_RESPECT_TO_ORIENTATION_OF_CURVE"
#define MAXIMUM_ALPHA_TO_BETA_GRADIENT_RATIO_NAME "MAXIMUM_ALPHA_TO_BETA_GRADIENT_RATIO"
#define USE_EDGISE_3X3_KERNEL_NAME "USE_EDGISE_3X3_KERNEL"
#define USE_EDGISE_5X5_KERNEL_NAME "USE_EDGISE_5X5_KERNEL"
#define A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_5X5_KERNEL_NAME "A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_5X5_KERNEL"			//(-EDGE_LUMINOSITY_CONTRAST_THRESHOLD/5)
#define A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_3X3_KERNEL_NAME "A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_3X3_KERNEL" 			//(-EDGE_LUMINOSITY_CONTRAST_THRESHOLD/5)
#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD_NAME "HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD"								//NB this represents the optimised values for 2DOD, consider/test using (256*1.0) for 3DOD...!!

#define HALF_PIXEL_WIDTH (0.5)
#define QUADRATIC_FIT_KERNEL_SIZE_3X3 (3)
#define QUADRATIC_FIT_KERNEL_SIZE_5X5 (5)


/*
//LDopengl.h;
#define OR_SNAPSHOT_WINDOW_POSITION_X (0)	//dependent upon resolution of monitor - should be moved to command line parameter
#define OR_SNAPSHOT_WINDOW_POSITION_Y (950)	//dependent upon resolution of monitor - should be moved to command line parameter

//ORimageComparison.h;
#define OR_IMAGE_COMPARISON_HAS_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION (0.0)				//not tested or used yet
#define OR_IMAGE_COMPARISON_HAS_STARK_LOCAL_CONTRAST_MIN_AVERAGE_COL_DEVIATION (0.0)			//not tested or used yet
#define OR_IMAGE_COMPARISON_HAS_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION (30.0)		//5
#define OR_IMAGE_COMPARISON_HAS_STARK_CONTRAST_WRT_AVERAGE_COLOUR_MIN_AVERAGE_COL_DEVIATION (20.0)
//#define OR_USE_OLD_BUGGY_BUT_WORKS_CODE
#ifdef OR_USE_OLD_BUGGY_BUT_WORKS_CODE
	#define IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR_BASE (119.465)
#else
	#define IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR_BASE (68.2656)
#endif
#define IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR (IMAGE_COMPARISON_MISFIT_AVG_PIXEL_COMPARISON_HUE_ERROR_BASE * 3)		//see calcaverageerror.cpp/genHueCompAvgErr.cpp for derivation
#define OR_IMAGE_COMPARISON_STARK_LOCAL_DEVIATION_MIN_MIN_COL_DIFF (10.0)
//#define OR_IMAGE_COMPARISON_USE_OLD_AVERAGE_CONTRAST_THRESHOLDING	//needs to be tested when this is removed
#ifdef OR_IMAGE_COMPARISON_USE_OLD_AVERAGE_CONTRAST_THRESHOLDING
	#define OR_IMAGE_COMPARISON_MAX_TOTAL_NUM_STARK_LOCAL_DEVIATIONS (100.0/(28*28))
#else
	#define OR_IMAGE_COMPARISON_MAX_TOTAL_NUM_STARK_LOCAL_DEVIATIONS (100.0/(28*28/2))
#endif
#define OR_IMAGE_COMPARISON_STARK_LOCAL_CONTRAST_MIN_AVG_COL_DIFF (10.0)	//needs to be tested
//#define OR_IMAGE_COMPARISON_MIN_TOTAL_NUM_STARK_LOCAL_CONTRASTS (100.0/(28*28/2))

//ORoperations.h;
#define XYCOORDINATES_CONVERSION_INTO_PIXELS (0.05)	//default 0.0002
#define MAX_FEATURE_DISTANCE_ERROR_USING_DEPTH_MAP_METHOD (5)	//in pixel units
#define MAX_FEATURE_DISTANCE_ERROR_USING_POINT_MAP_METHOD (XYCOORDINATES_CONVERSION_INTO_PIXELS * MAX_FEATURE_DISTANCE_ERROR_USING_DEPTH_MAP_METHOD)	//in world units		//OLD;(0.001)

//ORpixelMaps.h;
#define ESTIMATE_MAX_DEPTH_GRADIENT (0.1)
#define ESTIMATE_MAX_DEPTH_GRADIENT_CONTRAST (0.1)
#define DEPTH_GRADIENT_CONTRAST_THRESHOLD (0.1)


#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)
#ifdef OR_USE_CONTRAST_CALC_METHOD_C
	#define DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_INTERPIXEL (true)
	#define DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH (DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL)
	#define DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT (DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL)
#else
	#define DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_INTERPIXEL (false)
	#define DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH (DEPTH_GRADIENT_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL)
	#define DEFAULT_DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT (DEPTH_GRADIENT_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL)
#endif

#define NORMAL_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define NORMAL_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define NORMAL_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define NORMAL_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)
#ifdef OR_USE_CONTRAST_CALC_METHOD_C
	#define DEFAULT_NORMAL_MAP_GENERATION_INTERPIXEL (true)
	#define DEFAULT_NORMAL_MAP_GENERATION_KERNEL_WIDTH (NORMAL_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL)
	#define DEFAULT_NORMAL_MAP_GENERATION_KERNEL_HEIGHT (NORMAL_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL)
#else
	#define DEFAULT_NORMAL_MAP_GENERATION_INTERPIXEL (false)
	#define DEFAULT_NORMAL_MAP_GENERATION_KERNEL_WIDTH (NORMAL_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL)
	#define DEFAULT_NORMAL_MAP_GENERATION_KERNEL_HEIGHT (NORMAL_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL)
#endif

//RTpixelMaps.h;

#define CONTRAST_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define CONTRAST_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)
#ifdef OR_USE_CONTRAST_CALC_METHOD_C
	#define DEFAULT_CONTRAST_MAP_GENERATION_INTERPIXEL (true)
	#define DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH (CONTRAST_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL)
	#define DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT (CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL)
#else
	#define DEFAULT_CONTRAST_MAP_GENERATION_INTERPIXEL (false)
	#define DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH (CONTRAST_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL)
	#define DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT (CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL)
#endif



//ORquadraticFit.h;
#define MAXIMUM_GRADIENT_OF_CURVATURE_WITH_RESPECT_TO_ORIENTATION_OF_CURVE (10.0)
#define MAXIMUM_ALPHA_TO_BETA_GRADIENT_RATIO (0.7)
#define USE_EDGISE_3X3_KERNEL
//#define USE_EDGISE_5X5_KERNEL
#define A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_5X5_KERNEL (-20.0) 				//(-EDGE_LUMINOSITY_CONTRAST_THRESHOLD/5)
#define A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_3X3_KERNEL (-30.0) 				//(-EDGE_LUMINOSITY_CONTRAST_THRESHOLD/5)
#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (256*1.5)						//NB this represents the optimised values for 2DOD, consider/test using (256*1.0) for 3DOD...!!
#define HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/4.0)		//NB this represents the optimised values for 2DOD, consider/test using (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/4.0) for 3DOD...!!
#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD*10.0)
*/
/*
#ifdef USE_EDGISE_5X5_KERNEL
	#define QUADRATIC_FIT_KERNEL_SIZE (QUADRATIC_FIT_KERNEL_SIZE_5X5)
	#define ZERO_CROSSING_POSITION_THRESHOLD (HALF_PIXEL_WIDTH)
	#define A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD (A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_5X5_KERNEL)
#elif defined USE_EDGISE_3X3_KERNEL
	#define QUADRATIC_FIT_KERNEL_SIZE (QUADRATIC_FIT_KERNEL_SIZE_3X3)
	#define ZERO_CROSSING_POSITION_THRESHOLD (HALF_PIXEL_WIDTH)
	#define A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD (A3A4_COEFFICIENT_NEGATIVE_CURVATURE_POINT_THRESHOLD_3X3_KERNEL)
#endif
*/



//OR OPTIMISATION IMAGE CROPPING VARIABLES...

extern int WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE;
extern int OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO;
extern int OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO;	//has to result in a small image <= 8x8 pixels (single DCT block)

extern int OR_METHOD_2DOD_NORM_SNAPSHOT_X;	//secondary
extern int OR_METHOD_2DOD_NORM_SNAPSHOT_Y;	//secondary
extern int OR_METHOD_3DOD_NORM_SNAPSHOT_X;	//secondary
extern int OR_METHOD_3DOD_NORM_SNAPSHOT_Y;	//secondary

/*
extern int OR_METHOD_XDOD_SNAPSHOT_SIZE;			//must choose largest snapshot out of 2DOD and 3DOD
extern int OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE;		//must choose largest snapshot out of 2DOD and 3DOD
*/
extern bool OR_METHOD_2DOD_USE_NORM_SNAPSHOT_CROP;
extern bool OR_METHOD_3DOD_USE_NORM_SNAPSHOT_CROP;
extern int OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_X;
extern int OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_Y;
extern double OR_METHOD_2DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH;
extern int OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_X;
extern int OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_Y;
extern double OR_METHOD_3DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH;


#define WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE_NAME "WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE"
#define OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO_NAME "OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO"
#define OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO_NAME "OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO"	//has to result in a small image <= 8x8 pixels (single DCT block)

#define OR_METHOD_2DOD_NORM_SNAPSHOT_X_NAME "OR_METHOD_2DOD_NORM_SNAPSHOT_X"	//secondary
#define OR_METHOD_2DOD_NORM_SNAPSHOT_Y_NAME "OR_METHOD_2DOD_NORM_SNAPSHOT_Y"	//secondary
#define OR_METHOD_3DOD_NORM_SNAPSHOT_X_NAME "OR_METHOD_3DOD_NORM_SNAPSHOT_X"	//secondary
#define OR_METHOD_3DOD_NORM_SNAPSHOT_Y_NAME "OR_METHOD_3DOD_NORM_SNAPSHOT_Y"	//secondary

#define OR_METHOD_XDOD_SNAPSHOT_SIZE_MAX (100*100)			//must choose largest snapshot out of 2DOD and 3DOD
#define OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE_MAX (25*25)	//must choose largest snapshot out of 2DOD and 3DOD

#define OR_METHOD_2DOD_PREDEFINED_T_WIDTH (1.0)
#define OR_METHOD_2DOD_PREDEFINED_T_HEIGHT (0.866025404)	//sqrt(pow(1.0,2) - pow(0.5, 2))
#define OR_METHOD_2DOD_PREDEFINED_T_MINX (-(OR_METHOD_2DOD_PREDEFINED_T_WIDTH/2.0))
#define OR_METHOD_2DOD_PREDEFINED_T_MAXX ((OR_METHOD_2DOD_PREDEFINED_T_WIDTH/2.0))
#define OR_METHOD_2DOD_PREDEFINED_T_MINY (0.0)
#define OR_METHOD_2DOD_PREDEFINED_T_MAXY (OR_METHOD_2DOD_PREDEFINED_T_HEIGHT)
#define OR_METHOD_2DOD_PREDEFINED_T_IMAGINGOFFSET_X (0.0)										//such that PREDEFINED_T is in the centre of view
#define OR_METHOD_2DOD_PREDEFINED_T_IMAGINGOFFSET_Y (OR_METHOD_2DOD_PREDEFINED_T_HEIGHT/2.0)	//such that PREDEFINED_T is in the centre of view


/*
#define WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE (104)

#ifdef TEMP_INCREASE_GENERATED_DATA_IMAGE_SIZE
	#define OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO (8)	//has to result in a small image <= 8x8 pixels (single DCT block)
#else
	#define OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO (4)
#endif
#define OR_METHOD_2DOD_NORM_SNAPSHOT_X (OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO*(OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_BLOCK_SIZE-1))	//Eg 28	[must be divisible by OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO]
#define OR_METHOD_2DOD_NORM_SNAPSHOT_Y (OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO*(OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_BLOCK_SIZE-1)) 	//Eg 28	[must be divisible by OR_METHOD_2DOD_USE_SMALL_IMAGE_RATIO]

#ifdef TEMP_INCREASE_GENERATED_DATA_IMAGE_SIZE
	#define OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO (10)	//has to result in a small image <= 8x8 pixels (single DCT block)
#else
	#define OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO (5)	//has to result in a small image <= 8x8 pixels (single DCT block)
#endif
#define OR_METHOD_3DOD_NORM_SNAPSHOT_X (OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO*OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_BLOCK_SIZE)		//eg 40
#define OR_METHOD_3DOD_NORM_SNAPSHOT_Y (OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO*OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_BLOCK_SIZE)		//eg 40


#define OR_METHOD_XDOD_SNAPSHOT_SIZE (OR_METHOD_3DOD_NORM_SNAPSHOT_X*OR_METHOD_3DOD_NORM_SNAPSHOT_Y)			//must choose largest snapshot out of 2DOD and 3DOD
#define OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE ((OR_METHOD_3DOD_NORM_SNAPSHOT_X/OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO)*(OR_METHOD_3DOD_NORM_SNAPSHOT_Y/OR_METHOD_3DOD_USE_SMALL_IMAGE_RATIO))	//must choose largest snapshot out of 2DOD and 3DOD

#define OR_METHOD_2DOD_PREDEFINED_T_WIDTH (1.0)
#define OR_METHOD_2DOD_PREDEFINED_T_HEIGHT (0.866025404)	//sqrt(pow(1.0,2) - pow(0.5, 2))
#define OR_METHOD_2DOD_PREDEFINED_T_MINX (-(OR_METHOD_2DOD_PREDEFINED_T_WIDTH/2.0))
#define OR_METHOD_2DOD_PREDEFINED_T_MAXX ((OR_METHOD_2DOD_PREDEFINED_T_WIDTH/2.0))
#define OR_METHOD_2DOD_PREDEFINED_T_MINY (0.0)
#define OR_METHOD_2DOD_PREDEFINED_T_MAXY (OR_METHOD_2DOD_PREDEFINED_T_HEIGHT)
#define OR_METHOD_2DOD_PREDEFINED_T_IMAGINGOFFSET_X (0.0)										//such that PREDEFINED_T is in the centre of view
#define OR_METHOD_2DOD_PREDEFINED_T_IMAGINGOFFSET_Y (OR_METHOD_2DOD_PREDEFINED_T_HEIGHT/2.0)	//such that PREDEFINED_T is in the centre of view

#ifdef LINUX		//or if WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE is < OR_METHOD_XDOD_NORM_SNAPSHOT_X
	//Note linux supports windows of arbitrary size

	#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_GAUSSIAN_PREPROCESSOR_METHOD1
		//#define OR_METHOD_DO_NOT_CULL_SNAPSHOT	- needs to be made dynamic
		#define OR_METHOD_2DOD_USE_NORM_SNAPSHOT_CROP	//CURRENTLY REQUIRES OPENGL(?)
		#define OR_METHOD_3DOD_USE_NORM_SNAPSHOT_CROP	//CURRENTLY REQUIRES OPENGL(?)
		#define OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_X (OR_IMAGE_COMPARISON_DECISION_TREE_GAUSSIAN_KERNEL_SIZE/2)
		#define OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_Y (OR_IMAGE_COMPARISON_DECISION_TREE_GAUSSIAN_KERNEL_SIZE/2)
		#define OR_METHOD_2DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (double(OR_METHOD_2DOD_NORM_SNAPSHOT_X+(OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_X*2))/double(OR_METHOD_2DOD_NORM_SNAPSHOT_X))
		#define OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_X (OR_IMAGE_COMPARISON_DECISION_TREE_GAUSSIAN_KERNEL_SIZE/2)
		#define OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_Y (OR_IMAGE_COMPARISON_DECISION_TREE_GAUSSIAN_KERNEL_SIZE/2)
		#define OR_METHOD_3DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (double((OR_METHOD_3DOD_NORM_SNAPSHOT_X+(OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_X*2))/double(OR_METHOD_3DOD_NORM_SNAPSHOT_X))
	#else
		#define OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_X (0)
		#define OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_Y (0)
		#define OR_METHOD_2DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (1.0)
		#define OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_X (0)
		#define OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_Y (0)
		#define OR_METHOD_3DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (1.0)
	#endif


#else	//nb the following will only work when WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE is >> OR_METHOD_XDOD_NORM_SNAPSHOT_X
	//Note windows enforces a minimum horizontal windows size of 104 pixels
	#define OR_METHOD_2DOD_USE_NORM_SNAPSHOT_CROP	//CURRENTLY REQUIRES OPENGL(?)
	#define OR_METHOD_3DOD_USE_NORM_SNAPSHOT_CROP	//CURRENTLY REQUIRES OPENGL(?)
	#define OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_X ((WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE-OR_METHOD_2DOD_NORM_SNAPSHOT_X)/2)
	#define OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_Y ((WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE-OR_METHOD_2DOD_NORM_SNAPSHOT_Y)/2)
	#define OR_METHOD_2DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (double(OR_METHOD_2DOD_NORM_SNAPSHOT_X+(OR_METHOD_2DOD_NORM_SNAPSHOT_CROP_X*2))/double(OR_METHOD_2DOD_NORM_SNAPSHOT_X))	//#define OR_METHOD_2DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (double(WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE)/double(OR_METHOD_2DOD_NORM_SNAPSHOT_X))
	#define OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_X ((WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE-OR_METHOD_3DOD_NORM_SNAPSHOT_X)/2)
	#define OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_Y ((WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE-OR_METHOD_3DOD_NORM_SNAPSHOT_X)/2)
	#define OR_METHOD_3DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (double((OR_METHOD_3DOD_NORM_SNAPSHOT_X+(OR_METHOD_3DOD_NORM_SNAPSHOT_CROP_X*2))/double(OR_METHOD_3DOD_NORM_SNAPSHOT_X))	//#define OR_METHOD_3DOD_NORM_SNAPSHOT_UNCROPPED_WIDTH_TO_CROPPED_WIDTH (double(WINDOWS_MINIMUM_HORIZONTAL_WINDOW_SIZE)/double(OR_METHOD_3DOD_NORM_SNAPSHOT_X))

#endif
*/


//OR DISPLAY VARIABLES...

extern bool OR_PRINT_ALGORITHM_PROGRESS;		//true in xml/testing
extern bool OR_PRINT_ALGORITHM_AND_TIME_DETAILS;	//true in xml/testing
extern bool OR_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL;

extern bool OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML;	//true in xml/testing
extern bool OR_GENERATE_IMAGE_COMPARITOR_RESULTS_ALLOW_CONFIDENTIAL;	//true in xml/testing
extern bool OR_GENERATE_IMAGE_COMPARITOR_RESULTS_NO_EXPLICIT_CONFIDENTIAL_WARNINGS;	//true in xml/testing
extern bool DEMO_TO_CUSTOMER_HIDE_T_FROM_VIEW;		//for 2DOD, this will stop data outside of the normalised triangle object data from being culled
extern char OR_GENERATE_IMAGE_COMPARITOR_RESULTS_FNAME[];

#define OR_PRINT_ALGORITHM_PROGRESS_NAME "OR_PRINT_ALGORITHM_PROGRESS"		//true in xml/testing
#define OR_PRINT_ALGORITHM_AND_TIME_DETAILS_NAME "OR_PRINT_ALGORITHM_AND_TIME_DETAILS"	//true in xml/testing
#define OR_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL_NAME "OR_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL"

#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML_NAME "OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML"	//true in xml/testing
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_ALLOW_CONFIDENTIAL_NAME "OR_GENERATE_IMAGE_COMPARITOR_RESULTS_ALLOW_CONFIDENTIAL"	//true in xml/testing
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_NO_EXPLICIT_CONFIDENTIAL_WARNINGS_NAME "OR_GENERATE_IMAGE_COMPARITOR_RESULTS_NO_EXPLICIT_CONFIDENTIAL_WARNINGS"	//true in xml/testing
#define DEMO_TO_CUSTOMER_HIDE_T_FROM_VIEW_NAME "DEMO_TO_CUSTOMER_HIDE_T_FROM_VIEW"		//for 2DOD, this will stop data outside of the normalised triangle object data from being culled
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_FNAME_NAME "OR_GENERATE_IMAGE_COMPARITOR_RESULTS_FNAME"

#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML_PRINT_OBJECT_NAMES

/*
//display important;
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_NO_EXPLICIT_CONFIDENTIAL_WARNINGS
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_ALLOW_CONFIDENTIAL
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML_PRINT_OBJECT_NAMES

//display general;
#define OR_PRINT_ALGORITHM_PROGRESS
#define OR_PRINT_ALGORITHM_AND_TIME_DETAILS
//#define OR_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL

//#define DEMO_TO_CUSTOMER_HIDE_T_FROM_VIEW		//for 2DOD, this will stop data outside of the normalised triangle object data from being culled
#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_FNAME "imageComparitorResultsForNormalisedSnapshots.html"

#ifndef TEST_VIEWTIME_SPEED_Z_FOR_WEBSITE
	#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML
#endif
#ifdef OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML
	#ifndef OR_GENERATE_IMAGE_COMPARITOR_RESULTS_ALLOW_CONFIDENTIAL
		#define DEMO_TO_CUSTOMER_HIDE_T_FROM_VIEW
	#endif
#endif
*/



//OR ACCURACY/TUNING VARIABLES...

extern double OR_IMAGE_COMPARITOR_MATCH_ERROR_THRESHOLD;

#define OR_IMAGE_COMPARITOR_MATCH_ERROR_THRESHOLD_NAME "OR_IMAGE_COMPARITOR_MATCH_ERROR_THRESHOLD"

/*
#ifdef OR_USE_OLD_BUGGY_BUT_WORKS_CODE
	#define OR_IMAGE_COMPARITOR_MATCH_ERROR_THRESHOLD (0.3)
#else
	#ifdef OR_USE_STAR_MAPS
		#define OR_IMAGE_COMPARITOR_MATCH_ERROR_THRESHOLD (0.01)
	#else
		#define OR_IMAGE_COMPARITOR_MATCH_ERROR_THRESHOLD (0.2)	//default; 0.2
	#endif
#endif
*/






//OR TRANSFORMATION ACCURACY VARIABLES...

extern bool OR_METHOD_3DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST;
extern bool OR_METHOD_2DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST;
extern double POLYGON_MIN_ANGLE_DEGREES;

extern double OR_METHOD3DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON;	//this needs to be made dynamic in the future! [based upon distance object is away from pov]
extern double OR_METHOD2DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON;	//100 //20


#define OR_METHOD_3DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST_NAME "OR_METHOD_3DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST"
#define OR_METHOD_2DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST_NAME "OR_METHOD_2DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST"
#define POLYGON_MIN_ANGLE_DEGREES_NAME "POLYGON_MIN_ANGLE_DEGREES"

#define OR_METHOD3DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON_NAME "OR_METHOD3DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON"	//this needs to be made dynamic in the future! [based upon distance object is away from pov]
#define OR_METHOD2DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON_NAME "OR_METHOD2DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON"	//100 //20
/*
#define OR_METHOD_3DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST
#define OR_METHOD_2DOD_USE_POLYGON_MIN_MAX_INTERNAL_ANGLE_TEST
#define POLYGON_MIN_ANGLE_DEGREES (10.0)

#define OR_METHOD3DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON (20.0)	//this needs to be made dynamic in the future! [based upon distance object is away from pov]
#define OR_METHOD2DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON (20.0)	//100 //20
//#define OR_USE_BAD_ADVANCED_AREA_OF_T_TEST

#define OR_METHOD3DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON (0.1)	//this needs to be made dynamic in the future! [based upon distance object is away from pov]

*/



//OR_IMAGE_COMPARISON_AVERAGE_RGB_DEV_BINNING...

extern int OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_NUM_DISTINCT_VALS_PER_COL;
extern int OR_IMAGE_COMPARISON_AVERAGE_RGB_DEV_BINNING_MULTIPLIER;

#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_NUM_DISTINCT_VALS_PER_COL_NAME "OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_NUM_DISTINCT_VALS_PER_COL"
#define OR_IMAGE_COMPARISON_AVERAGE_RGB_DEV_BINNING_MULTIPLIER_NAME "OR_IMAGE_COMPARISON_AVERAGE_RGB_DEV_BINNING_MULTIPLIER"

#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_NO_BINS_TO_COMPARE (3)

/*
#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_NUM_DISTINCT_VALS_PER_COL (20)
#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_NO_BINS_TO_COMPARE (3)
*/



//OR OPTIMISATION GEOMETRIC COMPARISON...

extern bool OR_METHOD_ONLY_USE_ONE_POLY_PER_FEATURE_FAST_BUT_LOW_REDUNDANCY;			//untested - default OFF
extern bool OR_METHOD_ONLY_USE_TWO_NEAREST_FEATURES_TO_COMPARE_FAST_BUT_LOW_REDUNDANCY;		//untested - default OFF

extern int NUMBER_OF_POLYGONS_PER_FEATURE;
extern int OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE;

extern int OR_METHOD_NUM_NEARBY_FEATURES_TO_TRANSFORM;

#define OR_METHOD_ONLY_USE_ONE_POLY_PER_FEATURE_FAST_BUT_LOW_REDUNDANCY_NAME "OR_METHOD_ONLY_USE_ONE_POLY_PER_FEATURE_FAST_BUT_LOW_REDUNDANCY"
#define OR_METHOD_ONLY_USE_TWO_NEAREST_FEATURES_TO_COMPARE_FAST_BUT_LOW_REDUNDANCY_NAME "OR_METHOD_ONLY_USE_TWO_NEAREST_FEATURES_TO_COMPARE_FAST_BUT_LOW_REDUNDANCY"

#define NUMBER_OF_POLYGONS_PER_FEATURE_NAME "NUMBER_OF_POLYGONS_PER_FEATURE"
#define OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE_NAME "OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE"


extern double OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR;
extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE;

extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_RANGE;
extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_RANGE;

extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_SEPARATION;
extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_SEPARATION;

extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_X_BINS;	//(40)
extern double OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_Y_BINS;	//(40)

#define OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR_NAME "OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR"
#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE_NAME "OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE"

#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_BINS_TO_COMPARE_X (3)
#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_BINS_TO_COMPARE_Y (3)

#define OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE_MAX (10)

/*
#ifdef OR_METHOD_GEOMETRIC_COMPARISON

	#ifdef OR_METHOD_ONLY_USE_ONE_POLY_PER_FEATURE_FAST_BUT_LOW_REDUNDANCY
		#define NUMBER_OF_POLYGONS_PER_FEATURE (1) 		//default; 1
	#else
		#define NUMBER_OF_POLYGONS_PER_FEATURE (3) 		//default; 3
	#endif

	#ifdef OR_METHOD_ONLY_USE_TWO_NEAREST_FEATURES_TO_COMPARE_FAST_BUT_LOW_REDUNDANCY
		#define OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE (2)	//default; 4, 10 will reduce speed but increase redundancy [due to bug?]
	#else
		#define OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE (4)	//default; 4, 10 will reduce speed but increase redundancy [due to bug?]
	#endif

	#ifdef DEBUG_OR_TH_METHOD_3DOD_TEST_COMPARE_OT_FEATURES
		#define OR_METHOD_NUM_NEARBY_FEATURES_TO_TRANSFORM (OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE - OR_METHOD_POLYGON_NUMBER_OF_SIDES)	//with 3DOD, all features including those on the OT may be compared, so less additional nearby features are required for transformation
	#else
		#define OR_METHOD_NUM_NEARBY_FEATURES_TO_TRANSFORM (OR_METHOD_NUM_NEARBY_FEATURES_TO_COMPARE)	//NB transformed 3DOD OT features only differ from each other in terms of they scaling, where as transformed 2DOD OT features do not differ at all. All other 3DOD/2DOD transformed features differ.
	#endif

	#ifndef OR_IMAGE_COMPARISON_SQL_GET_TEST_DATA_FROM_SQL

		//#ifdef OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING
			//cannot use OR_METHOD_GEOMETRIC_COMPARISON_USE_TEST_RGB_MAP_OPTIMISATION when rgb bin check is require and not getting test data from sql
		//#else
			#define OR_METHOD_GEOMETRIC_COMPARISON_USE_TEST_RGB_MAP_OPTIMISATION
		//#endif

	#else
		//#ifndef OR_IMAGE_COMPARISON_SMALL_HUE_DEV_MAP_COMPARISON
			#define OR_METHOD_GEOMETRIC_COMPARISON_USE_TEST_RGB_MAP_OPTIMISATION		//cannot use this optimisation here if small rgb dev comparison is performed
		//#endif
	#endif

	//#define USE_GEO_TEST_GRID_SIZE_LARGE	//use large grid size when using decision tree since grid must be deterministic - and want to reduce the pertinence of antialiasing?

	#ifdef USE_GEO_TEST_GRID_SIZE_LARGE
		#define OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR (0.5)
	#else
		#define OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR (0.3)
	#endif

	#ifdef USE_GEO_TEST_GRID_SIZE_LARGE
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE (6.0)	//OLD 12.5
	#else
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE (6.0)		//nearest features checked for geo hashing can lie within 8x the extent of the OT, assuming OT has a side diameter of 1
	#endif
	#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_RANGE (OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE*2)
	#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_RANGE (OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NEAREST_FEATURE_MAX_DISTANCE*2)
	#ifdef USE_GEO_TEST_GRID_SIZE_LARGE
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_SEPARATION (OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR)
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_SEPARATION (OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR)
	#else
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_SEPARATION (OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR)
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_SEPARATION (OR_GEOMETRIC_CHECK_COMPARISON_MAX_ERROR)
	#endif

	#ifdef USE_GEO_TEST_GRID_SIZE_LARGE
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_X_BINS (24)	//OLD 50.0		//((long)(((double)OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_RANGE)/OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_SEPARATION))
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_Y_BINS (24)	//OLD 50.0		//((long)(((double)OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_RANGE)/OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_SEPARATION))
	#else
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_X_BINS (40)				 //((long)(((double)OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_RANGE)/OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_X_BIN_SEPARATION))
		#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_Y_BINS (40)				 //((long)(((double)OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_RANGE)/OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_Y_BIN_SEPARATION))
	#endif

	#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_BINS_TO_COMPARE_X (3)
	#define OR_METHOD_GEOMETRIC_COMPARISON_OPTIMISED_FILE_IO_V2_NO_BINS_TO_COMPARE_Y (3)



	//#define OR_METHOD_TRANSFORM_KEY_OT_FEATURES
	#ifdef OR_METHOD_TRANSFORM_KEY_OT_FEATURES
		#define OR_METHOD_CREATE_OT_FEATURES_FILE
	#endif

	//#define OR_METHOD_TRANSFORM_ALL_FEATURES		//do not use this; it is inefficient
	#ifdef OR_METHOD_TRANSFORM_ALL_FEATURES
		#define OR_METHOD_CREATE_ALL_FEATURES_FILE
	#endif


	#ifdef OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO

		#define OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TEST_FILE_IO

		#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE_ALWAYS
		#ifdef OR_METHOD_CREATE_NEARBY_FEATURES_FILE_ALWAYS
			#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE
		#endif

	#elif defined OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO_V2

		#define OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TEST_FILE_IO

		#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE_ALWAYS
		#ifdef OR_METHOD_CREATE_NEARBY_FEATURES_FILE_ALWAYS
			#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE
		#endif

	#elif defined OR_METHOD_GEOMETRIC_COMPARISON_NON_OPTIMISED_FILE_IO

	#elif defined TEMPTEST3GEOACCURACY

		#ifdef OR_METHOD_TRANSFORM_NEARBY_FEATURES
			#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE_ALWAYS
		#endif

	#else
		//OR_IMAGE_COMPARISON_GEOMETRIC_COMPARISON_BINNING....

		#ifndef OR_IMAGE_COMPARISON_SQL_GET_TEST_DATA_FROM_SQL
			#define OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TEST_FILE_IO
			#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE_DURING_TEST
			#ifdef OR_METHOD_CREATE_NEARBY_FEATURES_FILE_DURING_TEST
				#define OR_METHOD_CREATE_NEARBY_FEATURES_FILE
			#endif
			//#define OR_SQL_DATABASE_STORE_ALL_NEARBY_AND_OT_FEATURES
		#endif


	#endif

*/



//OR OPTIMISATION SMALL IMAGE COMPARISON VARIABLES...

extern bool OR_METHOD_USE_SMALL_IMAGE_RATIO_IGNORE_BG_COMPARISON;
extern double OR_IMAGE_COMPARITOR_SMALL_MATCH_ERROR_THRESHOLD;
#define OR_IMAGE_COMPARITOR_SMALL_MATCH_ERROR_THRESHOLD_NAME "OR_IMAGE_COMPARITOR_SMALL_MATCH_ERROR_THRESHOLD"

/*
#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON
	#define OR_METHOD_USE_SMALL_IMAGE_RATIO_IGNORE_BG_COMPARISON
#endif
#define OR_IMAGE_COMPARITOR_SMALL_MATCH_ERROR_THRESHOLD (0.2)
*/



//OR SQL PIXMAPS VARIABLES...

extern int OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE_DATA_LENGTH;



//OR SPARE PARAMETERS VARIABLES...

extern bool OR_RULES_XML_SPARE_PARAMETER_1;
extern double OR_RULES_XML_SPARE_PARAMETER_2;	//this needs to be made dynamic in the future! [based upon distance object is away from pov]
#define OR_RULES_XML_SPARE_PARAMETER_1_NAME "OR_RULES_XML_SPARE_PARAMETER_1"
#define OR_RULES_XML_SPARE_PARAMETER_2_NAME "OR_RULES_XML_SPARE_PARAMETER_2"	//this needs to be made dynamic in the future! [based upon distance object is away from pov]












	/**********
	OR FEATURE DEBUG VARS - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

#define OR_QUADRATIC_FIT_DEBUG		//creates images of quadtratic fit detection process
#define OR_CONTIGUOUS_REGION_DEBUG	//creates images of feature detection process
#ifdef OR_CONTIGUOUS_REGION_DEBUG
	//#define OR_CONTIGUOUS_REGION_DEBUG_PRINT
	//#define OR_CONTIGUOUS_REGION_DEBUG2
	#define OR_CONTIGUOUS_REGION_DEBUG3
	//#define OR_CONTIGUOUS_REGION_DEBUG_PRINT_BOUNDARY_TRACE
	//#define OR_CONTIGUOUS_REGION_DEBUG_BOUNDARY_TRACE
#endif


	/**********
	OR FOURIER DEBUG VARS - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

//#define DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML		//displays DCT tables of arbitrary quality for all matches in HTML results file
#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
	#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_QUALITY_TEMP_STRING "-quality 20%"
#endif
//#define DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING		//displays all DCT table creations


	/**********
	OR SQL DEBUG VARS - displays all SQL commands - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

//#define OR_SQL_DATABASE_DEBUG		//maybe should not be used when DECISION_TREE is enabled (creates junk text to the display which might trigger off gterm). definately should not be used when OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE is enabled with gterm (creates alot of junk text to the display which might trigger off gterm)
#ifdef OR_SQL_DATABASE_DEBUG
	#define OR_SQL_DATABASE_DEBUG_COMPARISON_ONLY
#endif

	/**********
	OR DEBUG DECISION TREE RGB DEV MAP COMPARISON VARS - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

//#define DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD	//displays contrast thresholded RGB maps
//#define DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON_THRESHOLD
//#define DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON


	/**********
	OR DEBUG 3D MESH GENERATION VARS - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

//#define OR_DEBUG_RAYTRACE_INTERPOLATED_3D_MAP_WITH_ORIGINAL_VIEW
#define OR_DEBUG_SAVE_REFERNCE_LIST_TO_FILE


	/**********
	OR DEBUG 3DOD VARS - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

//#define OR_DEBUG_METHOD3DOD_POV
//#define OR_DEBUG_3DOD_POV

	/**********
	OR DEBUG VARS OLD - COMMENT THESE OUT FOR for proper/formal/release software build;
	***********/

//#define DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DO_NOT_USE_REAL_SQL_QUERY
//#define OR_METHOD3DOD_TEST	//temporary
//#define TEST_GEO		//temp (reduces number of objects and view points for software testing)
//#define OR_LOW_RAM		//only effects OR Test Harness
//#define DO_NOT_NORMALISE_POINT_NORMAL_MAP
//#define OR_DO_NOT_CHECK_FOR_ZERO_DIVISION_DURING_POINT_NORMAL_CALC

/*very old;
//#define OR_DEBUG_WORRY_ABOUT_DISPLAYING_2D_NET_PROPERLY
//#define OR_DEBUG_TRAIN_USING_FAR_INSUFFICIENT_NUMBER_EPOCHS
//#define OR_DEBUG_RT_LIGHTING_OR_SURFACE_COLOUR_REPEATABILITY
//#define OR_DEBUG_UNTHRESHOLDED_NN_FEED
//#define OR_DEBUG_RAYTRACE_INTERPOLATED_3D_MAP_WITH_ORIGINAL_VIEW
//#define OR_DEBUG_OLD_FEATURE_GENERATION_METHOD	//Old method is not working properly; need to translate corner coordinates into interpolated map coordiantes system
*/
/* extremely old;
//#define TEMP_TEST_HEITGER_FEATURE_THRESHOLD_IMAGE_SIZE_DEPENDENCE	//doesnt help
//#define TEMP_DEBUG_CONVERT
//#define TEMP_DEBUG_CONVERT2
//#define TEST_TIMES
//#define TEST_FEATURE_DETECTION_THRESHOLD_ON_A_NEW_OBJECT
#ifdef TEST_FEATURE_DETECTION_THRESHOLD_ON_A_NEW_OBJECT
#endif
*/






	/**********
	OR RAYTRACER ACCURACY RESOLUTION VARIABLES
	***********/

//#define OLDcalculateLuminosityLevelFromRGBMap
#define RT_CONVERT_LDR_OBJECT_SCALES_PROPERLY
#define RT_CONVERT_LDR_OBJECT_ROTATION_PROPERLY

//#define TRY_UNTESTED_SOFTWARE	//all the following are seriously untested
#ifdef TRY_UNTESTED_SOFTWARE
	#define RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY_VERSIONB (untested - may overcome no draw centre pixel line/column of object issue with RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY)
#else
	#define RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY
#endif


	/**********
	OR SQL DATABASE QUERY VARIABLES;
	***********/

//#ifdef OR_IMAGE_COMPARISON_DECISION_TREE



	#define OR_IMAGE_COMPARISON_DECISION_TREE_SQL		//else use file i/o
	#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_SQL
		#define OR_IMAGE_COMPARISON_DECISION_TREE_SINGLE_INSERT_STATEMENT_OPTIMISATION
	#endif

	#define OR_IMAGE_COMPARISON_DECISION_TREE_BIN_MAX_LENGTH (1000)

	//#define OR_IMAGE_COMPARISON_DECISION_TREE_SQL_DIRECT_ACCESS			//this has issues and has not yet been properly tested
	//#define OR_IMAGE_COMPARISON_DECISION_TREE_SQL_DIRECT_ACCESS_USE_JOIN_OPT	//probably has not yet been coded

	//#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_MULTIPLE	//not yet coded; records decision tree access data for multiple contrast thresholds on snapshot

	//#define OR_SQL_DATABASE_STORE_ALL_NEARBY_AND_OT_FEATURES	//this can be used with OR_IMAGE_COMPARISON_DECISION_TREE as nearby feature data is not taken and used from snapshot tables [only used in the definition of decision tree tables]

	#define OR_IMAGE_COMPARISON_DECISION_TREE_BINARY_TO_CHAR_CONVERSION_OPT		//not required always
	#define OR_IMAGE_COMPARISON_DECISION_TREE_STRING_MAX_LENGTH (1000)


	#ifndef OR_IMAGE_COMPARISON_DECISION_TREE_SQL
		#ifdef LINUX
			#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_DEFAULT_BASE_DIRECTORY "/home/rich/source/source/"
			#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_DEFAULT_NAME "BAIcomparator"
		#else
			#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_DEFAULT_BASE_DIRECTORY "c:/files/"
			#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_DEFAULT_NAME "BAIcomparator"
		#endif
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_DEFAULT_LIST_FILE_NAME "r.txt"
	#endif


	/***** OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING *****/

			//available methods;
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_HIGH_REDUNDANCY_DETERMINISTIC_BY_ITERATING_OVER_ALL_ADJACENT_BINS_FAST_RECOG_BUT_USE_MORE_HD		//option 2
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_HIGH_REDUNDANCY_DETERMINISTIC_BY_ITERATING_OVER_ALL_ADJACENT_BINS_SLOW_RECOG_BUT_USE_LESS_HD		//option 3
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_LOW_REDUNDANCY_NOT_DETERMINISTIC_FAST_RECOG_DO_NOT_ALLOW_EXCEPTIONS 					//option 1
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_FAST_BUT_USE_MORE_HD						//option 4
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_FAST_BUT_USE_MORE_HD
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_FAST_BUT_USE_MORE_HD_x2					//option 4b
		#endif
		#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_FAST_RECOG_AND_USE_LOW_HD	//option 5; coding this now
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_FAST_RECOG_AND_USE_LOW_HD
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LOW_RESOLUTION
			#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LOW_RESOLUTION
				#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_THRESHOLD (0.25)
			#else
				#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_THRESHOLD (0.0)
			#endif
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_NEG (1)
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_POS (2)
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_SAME (0)
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_DO_NOT_ALLOW_REPEATS	//option 1
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_DO_NOT_ALLOW_REPEATS_V2	//option 2

			//#ifndef OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_DO_NOT_ALLOW_REPEATS
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_LOOKUP_DO_NOT_ALLOW_REPEATS
			//#endif

			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LIMIT_PERMUTATIONS
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LIMIT_PERMUTATIONS_MAX_NUM_BIAS_BINS_RATIO (0.5)
		#endif

		#ifndef OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_HIGH_REDUNDANCY_DETERMINISTIC_BY_ITERATING_OVER_ALL_ADJACENT_BINS_SLOW_RECOG_BUT_USE_LESS_HD
			#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NO_EXPLICIT_FOR_LOOPS
		#endif



	/***** OR_IMAGE_COMPARISON_DECISION_TREE_AVERAGE_RGB_DEV_BINNING *****/



	/*****  OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING *****/

			//available methods;
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_FAST_BUT_USE_MORE_HD		//option 1
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_FAST_BUT_USE_MORE_HD
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_FAST_BUT_USE_MORE_HD_x2	//option 1b
		#endif
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_ALLOWING_EXCEPTIONS_SLOW_BUT_USE_LESS_HD		//option 2
		#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_FAST_RECOG_AND_USE_LOW_HD	//option 3; coding this now
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_FAST_RECOG_AND_USE_LOW_HD
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LOW_RESOLUTION
			#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LOW_RESOLUTION
				#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_THRESHOLD (0.25)
			#else
				#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_THRESHOLD (0.0)
			#endif
			#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_NEG (1)
			#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_POS (2)
			#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_SAME (0)
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_DO_NOT_ALLOW_REPEATS	//option 1
			#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_DO_NOT_ALLOW_REPEATS_V2	//option 2

			//#ifndef OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_DO_NOT_ALLOW_REPEATS
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GEOMETRIC_COMPARISON_BINNING_LOOKUP_DO_NOT_ALLOW_REPEATS
			//#endif

			#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LIMIT_PERMUTATIONS
			#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_SLOW_TO_TRAIN_REQUIRES_HIGH_MEM_BUT_HIGH_REDUNDANCY
				#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LIMIT_PERMUTATIONS_MAX_NUM_BIAS_BINS_RATIO (0.5)
			#else
				#define OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_DETERMINISTIC_BY_INTELLIGENT_BINNING_LIMIT_PERMUTATIONS_MAX_NUM_BIAS_BINS_RATIO (0.3)
			#endif
		#endif


	/***** OR_IMAGE_COMPARISON_DECISION_TREE_SMALL_HUE_DEV_MAP_COMPARISON *****/

		#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_METHOD_1_ALL_RGB_COMPONENTS_WITH_DIRECTION		//highest discrimination [recog speed], lowest redundancy
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_METHOD_2_ALL_RGB_COMPONENTS
		#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_METHOD_3_LUMINOSITY_ONLY				//highest redundancy, lowest discrimination [recog speed]

		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_RED_GT_NODE_NAME "a" 	//sanitised - rGT
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_RED_LT_NODE_NAME "b" 	//sanitised - rLT
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_GREEN_GT_NODE_NAME "a"	//sanitised - gGT
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_GREEN_LT_NODE_NAME "b" 	//sanitised - gLT
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_BLUE_GT_NODE_NAME "a" 	//sanitised - bGT
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_BLUE_LT_NODE_NAME "b" 	//sanitised - bLT
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_RED_NC_NODE_NAME "c"	//sanitised - rNOCHANGE		//should not be used
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_GREEN_NC_NODE_NAME "c"	//sanitised - gNOCHANGE		//should not be used
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_BLUE_NC_NODE_NAME "c"	//sanitised - bNOCHANGE		//should not be used
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_GT_NODE_NAME "a" 		//sanitised - GT		//luminosity map only
		#define OR_IMAGE_COMPARISON_DECISION_TREE_REFERENCE_NC_NODE_NAME "c"		//sanitised - NOCHANGE		//luminosity map only


			//ori/pos deviations [feature shifts]
		//#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_VIEW_DEVIATIONS
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_VIEW_DEVIATIONS
			#define OR_TEST_ORI_AND_POS_NOISE_DURING_TRANING_AND_TESTING
		#endif



		//gaussian
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_ORIGINAL_DESIGN_SMALL_HUE_DEV_MAP_COMPARISON_ONLY
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_GAUSSIAN_PREPROCESSOR_METHOD1	//this is designed to eliminate aliasing issues in decision tree generation
			#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_GAUSSIAN_PREPROCESSOR_METHOD2_IMAGEMAGICK_CONVERT_INTERPOLATION
			//#define OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_GAUSSIAN_PREPROCESSOR_METHOD3_GIMP_SCALE_IMAGE_INTERPOLATION	//Not yet coded - Scale Image using Gimp - produces best known scaled results [for small image comparison using DCT/fourier]
		#endif
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_GAUSSIAN_PREPROCESSOR_METHOD1
			#define OR_IMAGE_COMPARISON_DECISION_TREE_GAUSSIAN_KERNEL_SIGMA (2.0)
		#endif
		#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_GAUSSIAN_PREPROCESSOR_METHOD2_IMAGEMAGICK_CONVERT_INTERPOLATION
			#define OR_IMAGE_COMPARISON_DECISION_TREE_CONTRAST_THRESHOLD_FACTOR (5.0)	//needs to be dynamic based upon normalisation based upon average rgb values in image	//replace with EDGE_LUMINOSITY_CONTRAST_THRESHOLD at some stage???
		#else
			#define OR_IMAGE_COMPARISON_DECISION_TREE_CONTRAST_THRESHOLD_FACTOR (7.0)	//needs to be dynamic based upon normalisation based upon average rgb values in image	//replace with EDGE_LUMINOSITY_CONTRAST_THRESHOLD at some stage???
		#endif

		#define OR_IMAGE_COMPARISON_DECISION_TREE_GAUSSIAN_KERNEL_SIZE (5)

		#define RGB_CONTRAST_BOOLEAN_MAP_GENERATION_KERNEL_WIDTH (2)		//try 2 also
		#define RGB_CONTRAST_BOOLEAN_MAP_GENERATION_KERNEL_HEIGHT (2)		//try 2 also

		#define OR_IMAGE_COMPARISON_PREPROCESS_BOUNDARY_RATIO (0.1)	//10% padding added [each side] for snapshot preprocessor gaussian kernel application

//#endif


/**********
OR METHOD 3DOD VARIABLES;
***********/

#define OR_OVERWRITE_POINT_MAP_USING_CONSISTENT_POINT_MAP_CREATION

#define OR_METHOD_3DOD_IGNORE_OT_FEATURES_DURING_GEO_COMPARISON		//NB transformed 3DOD OT features only differ from each other in terms of they scaling, where as transformed 2DOD OT features do not differ at all. All other 3DOD/2DOD transformed features differ.

#define OR_METHOD_3DOD_USE_FORMAL_TRANSFORMATION_METHOD		//when all issues related to this are resolved and this becomes the default, an inverse definition name should be implemented for clarity
//#define OR_DEBUG_METHOD_3DOD


/**********
OR OPTIMISATION PRELIMINARY CONTRAST CHECK VARIABLES;
***********/

#define OR_METHOD_CHECK_SNAPSHOT_CONTRAST_BEFORE_SAVING_SNAPSHOT
//#define OR_METHOD_2DOD_DO_NOT_REQUIRE_SNAPSHOT_CONTRAST
#define OR_METHOD_3DOD_DO_NOT_REQUIRE_SNAPSHOT_CONTRAST
//#define OR_IMAGE_COMPARISON_REQUIRE_SNAPSHOT_STARK_LOCAL_CONTRAST		//not currently used


/**********
OR FUTURE GOOD OPTIMISATION VARIABLES;
***********/

#define OR_IMAGE_COMPARISON_COMPARE_RGB_DEV_MAPS_NOT_RGB_MAPS (false)		//case "true" is not yet coded; code this


/**********
OR SQL VARIABLES;
***********/

#define OR_IMAGE_COMPARISON_SQL										//no choice on this for release versions
#ifdef OR_IMAGE_COMPARISON_SQL

	#define OR_METHOD_GEOMETRIC_COMPARISON_BINNING		//required for current execution flow event though binning is not used in this case


	#define OR_MYSQL_DATABASE_NAME "objectRecog"
	#define OR_MYSQL_IP_ADDRESS_DEFAULT "localhost"
	#define OR_MYSQL_USER_NAME_DEFAULT "rich"
	#define OR_MYSQL_USER_PASSWORD_DEFAULT "Esteban7"
	#define OR_MYSQL_TABLE_NAME_TRAIN "s"	//snapshot
	#define OR_MYSQL_TABLE_NAME_TEST "st"	//snapshotTest
	#define OR_MYSQL_TABLE_NAME_DECISIONTREE "dt"	//decisionTree

	#define OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES (5) 	//eg " ... , "

	#define OR_MYSQL_FIELD_NAME_ID "ID"
	#define OR_MYSQL_FIELD_NAME_OBJECTNAME "objectName"
	#define OR_MYSQL_FIELD_NAME_TRAINORTESTNUM "objectNum"
	#define OR_MYSQL_FIELD_NAME_VIEWNUM "vNum"
	#define OR_MYSQL_FIELD_NAME_ZOOMNUM "zNum"
	#define OR_MYSQL_FIELD_NAME_POLYNUM "pNum"
	#define OR_MYSQL_FIELD_NAME_SIDENUM "sNum"
	#define OR_MYSQL_FIELD_NAME_OTNUM  "pBIndex"
	#define OR_MYSQL_FIELD_TYPE_ID (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_TYPE_OBJECTNAME (MYSQL_FIELD_TYPE_VARCHAR_8BIT)	//are var chars ok in SQL? or do they slow it down?
	#define OR_MYSQL_FIELD_TYPE_TRAINORTESTNUM (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_TYPE_VIEWNUM (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_TYPE_ZOOMNUM (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_TYPE_POLYNUM (MYSQL_FIELD_TYPE_INT_32BIT)	//should realistically be 16bit, and most commonly 8bit (<256 polys per snapshot)
	#define OR_MYSQL_FIELD_TYPE_SIDENUM (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_TYPE_OTNUM  (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_NAME_LENGTH_MAX (10)
	#define OR_MYSQL_FIELD_NAME_BASICS_MAX_LENGTH ((10 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES) * OR_MYSQL_FIELD_NAME_LENGTH_MAX)
	#define OR_MYSQL_FIELD_NAME_POINTTRANSFORMEDX "pxT"
	#define OR_MYSQL_FIELD_NAME_POINTTRANSFORMEDY "pyT"
	#define OR_MYSQL_FIELD_NAME_POINTTRANSFORMEDZ "pzT"
	#define OR_MYSQL_FIELD_TYPE_POINTTRANSFORMED (MYSQL_FIELD_TYPE_REAL_FLOAT_32BIT)
	#define OR_MYSQL_FIELD_NAME_POINTX "px"
	#define OR_MYSQL_FIELD_NAME_POINTY "py"
	#define OR_MYSQL_FIELD_NAME_POINTZ "pz"
	#define OR_MYSQL_FIELD_TYPE_POINT (MYSQL_FIELD_TYPE_REAL_FLOAT_32BIT)
	#define OR_MYSQL_FIELD_NAME_POINT_LENGTH (5 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)
	#define OR_MYSQL_FIELD_NAME_POINT_MAX_LENGTH (OR_MYSQL_FIELD_NAME_POINT_LENGTH * 6)
	#define OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BINS "d"			//not yet implemented - see JPEG code
	#define OR_MYSQL_FIELD_TYPE_DCT_COEFFICIENT_BINS (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BIN_ALL "dBin"		//combination of d0->d15
	#define OR_MYSQL_FIELD_TYPE_DCT_COEFFICIENT_BIN_ALL (MYSQL_FIELD_TYPE_BIG_INT_64BIT)
	#define OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BINS_LENGTH (3 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)	//eg d12
	#define OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BIN_ALL_LENGTH (4 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)
	#define OR_MYSQL_FIELD_NAME_GEO_BINS_X "pBinx"
	#define OR_MYSQL_FIELD_NAME_GEO_BINS_Y "pBiny"
	#define OR_MYSQL_FIELD_TYPE_GEO_BINS (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_NAME_GEO_BINS_XY "pBinxy"	//combination of pBinx1, pBiny1, pBinx2, pBiny2 etc	 //-enabling the binning of the combinations/permutations of transformed xy positions of nearby features of the 3 OT features
	#define OR_MYSQL_FIELD_TYPE_GEO_BINS_XY (MYSQL_FIELD_TYPE_INT_32BIT)
	#define OR_MYSQL_FIELD_NAME_GEO_BINS_LENGTH (5 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)
	#define OR_MYSQL_FIELD_NAME_GEO_BINS_XY_LENGTH (6 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)
	//#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_LUMINOSITY_BINS "colAvgLBin"
	//#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_HUE_BINS "colAvgHBin"
	//#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_SATURATION_BINS "colAvgSBin"
	#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_R_BINS "caABin"
	#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_G_BINS "caBBin"
	#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_B_BINS "caCBin"
	#define OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_BINS (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_BINS_LENGTH (6 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)
	#define OR_MYSQL_FIELD_NAME_COLOUR_AVERAGE_RGB_BINS "caBin"			//combination of colAvgLBin, colAvgHBin, and colAvgSBin
	#define OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_RGB_BINS (MYSQL_FIELD_TYPE_INT_32BIT)
	#define OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_RGB_BINS_LENGTH (5 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)
	#define OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_MAX_LENGTH (OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_BINS_LENGTH*3 + OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_RGB_BINS_LENGTH)
	#ifndef OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
	#define OR_MYSQL_FIELD_NAME_COMBINED_BINS "combinedBin" 		//combination of pBinxy and colAvgBin, [and ideally dBin, but not possibly at this stage]
	#define OR_MYSQL_FIELD_TYPE_COMBINED_BINS (MYSQL_FIELD_TYPE_BIG_INT_64BIT)	//this needs to be bigger than 64bit unless DCT coeff binning is disabled or seriously back scaled
	#endif
	#define OR_MYSQL_FIELD_NAME_SMALL_IMAGE_R "simA"	//not currently used,	//generally, binned normalised dev hue values are stored here for SQL small image comparison independent of lighting conditions
 	#define OR_MYSQL_FIELD_NAME_SMALL_IMAGE_G "simB"	//not currently used, 	//generally, binned normalised dev hue values are stored here for SQL small image comparison independent of lighting conditions
	#define OR_MYSQL_FIELD_NAME_SMALL_IMAGE_B "simC"	//not currently used, 	//generally, binned normalised dev hue values are stored here for SQL small image comparison independent of lighting conditions
	#define OR_MYSQL_FIELD_NAME_SMALL_IMAGE_LENGTH (4 + OR_MYSQL_FIELD_NAME_SPACING_BETWEEN_SQL_COMMAND_FIELD_REFERENCES)

	#define OR_MYSQL_FIELD_TYPE_SMALL_IMAGE (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_NAME_ALL_IMAGE_TEXT "alltext"
	#define OR_MYSQL_FIELD_TYPE_ALL_IMAGE_TEXT (MYSQL_FIELD_TYPE_TEXT_16BIT_NUM_CHARACTERS)

	#define OR_MYSQL_FIELD_NAME_TRAINORTESTNUM_TRAIN "1"
	#define OR_MYSQL_FIELD_NAME_TRAINORTESTNUM_TEST "0"




	#define OR_MYSQL_FIELD_NAME_DECISIONTREE_SNAPSHOT_REF_ID "srID"
	#define OR_MYSQL_FIELD_TYPE_DECISIONTREE_SNAPSHOT_REF_ID (MYSQL_FIELD_TYPE_TINY_INT_8BIT)
	#define OR_MYSQL_FIELD_NAME_DECISIONTREE_BIN "dtBin"
	#define OR_MYSQL_FIELD_TYPE_DECISIONTREE_BIN (MYSQL_FIELD_TYPE_TINYTEXT)		//max 255 characters		//maybe should use CHAR and BINARY instead


	#define OR_METHOD_3DOD_USE_SNAPSHOT_DEPTH_MAPS
	#define UNKNOWN_OPENGL_NOHIT_DEPTH (0.0)
	#define UNKNOWN_OPENGL_ESTIMATE_MAX_DEPTH (1.0)
	//#define FIX_OPENGL_3DOD_TIMING_BUG
	#define OR_METHOD_3DOD_USE_SNAPSHOT_DEPTH_MAPS_ADVANCED_RESAMPLING


	/***** OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING *****/

		//#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_REQUIREMENT_V1	//this has been tested		//ATTENTION: this option is no longer supported as OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NO_EXPLICIT_FOR_LOOPS is now enforced as true with decition tree code enabled
		#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_REQUIREMENT_V2	//this has been tested
		//#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_REQUIREMENT_V3	//this has been tested

		#ifdef OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_REQUIREMENT_V2
			#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NO_EXPLICIT_FOR_LOOPS
		#endif
		#ifdef OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_REQUIREMENT_V3
			#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NO_EXPLICIT_FOR_LOOPS
		#endif


		#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_MAX_DATA_LENGTH (4*4 + 1*10)	//4* signed 8bit decimal + 1*unsigned 32bit
		#define OR_MYSQL_FIELD_TYPE_GEO_BINS_MAX_LENGTH (OR_MYSQL_FIELD_NAME_GEO_BINS_LENGTH*4 + OR_MYSQL_FIELD_NAME_GEO_BINS_XY_LENGTH)


	#define OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NUM_GEO_BINNING_DIMENSIONS (2)	//OR_MYSQL_FIELD_NAME_GEO_BIN_X1 pBinx1, OR_MYSQL_FIELD_NAME_GEO_BIN_Y1 pBiny1, OR_MYSQL_FIELD_NAME_GEO_BIN_X2 pBinx2, OR_MYSQL_FIELD_NAME_GEO_BIN_Y2 pBiny2	- enabling the binning of the transformed xy positions of nearby features of the 3 OT features

	#define OR_LINEAR_COMBINATION_ARRAY_MAX_SIZE (104)	//OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS + OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_BINNING_NUM_GEO_BINNING_DIMENSIONS*2




	/***** OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING *****/

		//#define OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING_REQUIREMENT_V2
		#define OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING_REQUIREMENT_V3		//try this and speed compare with V2
		//#define OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_BINNING		//instead of hue dev binning

		#define OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING_MAX_DATA_LENGTH (3*3 + 1*12)	//3* 8bit decimal + 1* 32bit decimal
		#define OR_MYSQL_FIELD_TYPE_GEO_BINS_MAX_LENGTH (OR_MYSQL_FIELD_NAME_GEO_BINS_LENGTH*4 + OR_MYSQL_FIELD_NAME_GEO_BINS_XY_LENGTH)


	/***** OR_IMAGE_COMPARISON_AVERAGE_RGB_DEV_BINNING *****/



	/***** OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING *****/

		#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_REQUIREMENT_V2	//dont use this it is guarenteed to be very slow; 3^16 comparisons
		//#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_REQUIREMENT_V3
		//#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_REQUIREMENT_V4
		#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_REQUIREMENT_V3_MIN_NUM_SUCC_COMPARISONS_REUQIRED (OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS*2/3)
		#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_REQUIREMENT_V3_MIN_NUM_SUCC_COMPARISONS_REUQIRED_NORMALISED (2.0/3.0)


		/***** OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING *****/

		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_BINARY_TO_CHAR_CONVERSION_OPT

		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_Y_MAX (9)
		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCr_MAX (9)
		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCb_MAX (9)
		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_MAX (OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_Y_MAX + OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCr_MAX + OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS_YCb_MAX)

		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_CHROMA_SUBSAMPLING_ON "-sampling-factor 1x1"		//deterministic dct coeff comparison requirement
		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_CHROMA_SUBSAMPLING_OFF ""					//"2x1"


		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NO_BINS_TO_COMPARE (3)	//x +/-1, y+/- 1
		#define OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_MAX_NUM_DCT_COEFFICIENTS_1D (3)



		/*
		DCT-Y values used;
		-1      *-5      *0       -1      -1      0       0       0
		*3       *0       *-2      0       0       0       0       0
		*2       *1       0       0       0       0       0       0
		-3      0       1       1       0       0       0       0
		1       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0

		DCT-YCb values used;
		*-1     *1       1       0       0       0       0       0
		*2      0       0       0       0       0       0       0
		1       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0

		DCT-YCr values used;
		*-4     *2       1       0       0       0       0       0
		*0      0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0
		0       0       0       0       0       0       0       0

		[if OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BIN_ALL is used; dctall -> all binned using 5bit signed, so require a 64 bit integer 5*7 {DCT-Y} + 5*3 {DCT-YCb} + 5*3 {DCT-YCr}  = 60bit]
		*/

		#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_MAX_DATA_LENGTH (1*30 + OR_IMAGE_COMPARISON_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_NUM_DCT_COEFFICIENT_BINNING_DIMENSIONS*4)
			//number dct bins * signed 8bit decimal [-256 -> +256, 4 characters in length]
		#define OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_MAX_LENGTH (OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BINS_LENGTH + OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_BIN_ALL_LENGTH)




	/***** OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON *****/

		//#define OR_IMAGE_COMPARISON_SQL_DB_USE_RGB_8BIT_SMALL_MAP_QUERY_REQUIREMENT_V2
		//#define OR_IMAGE_COMPARISON_SQL_DB_USE_RGB_8BIT_SMALL_MAP_QUERY_REQUIREMENT_V3
		//#define OR_IMAGE_COMPARISON_SQL_DB_USE_RGB_8BIT_SMALL_MAP_QUERY_REQUIREMENT_V2_OR_V3
		#define OR_IMAGE_COMPARISON_SQL_DB_USE_RGB_8BIT_SMALL_MAP_QUERY_REQUIREMENT_V3_MIN_NUM_SUCC_COMPARISONS_REUQIRED_NORMALISED (2.0/3.0)
		#define OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON_MAX_ELEMENT_LENGTH (3)	//0->256, 3 characters
		#define OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON_MAX_DATA_LENGTH (OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE_MAX*3*OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON_MAX_ELEMENT_LENGTH)	//size * 8bit * 3 colours
		#define OR_MYSQL_FIELD_NAME_SMALL_IMAGE_MAX_LENGTH (OR_MYSQL_FIELD_NAME_SMALL_IMAGE_LENGTH * OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE_MAX*3)




	#define OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE_MAX_DATA_LENGTH (OR_METHOD_XDOD_SNAPSHOT_SIZE_MAX*3 + OR_METHOD_XDOD_SNAPSHOT_SIZE_MAX*3 + OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE_MAX*3 + OR_METHOD_XDOD_SNAPSHOT_SMALL_IMAGE_SIZE_MAX*3)
		/* for
 		unsigned char * rgbMapFacingPoly = new unsigned char[imageWidthFacingPoly*imageHeightFacingPoly*RGB_NUM];	OR;
		double * rgbDevIEnormalisedHueContrastMapFacingPoly = new double[imageWidthFacingPoly*imageHeightFacingPoly*VEC_MAP_VEC_NUM_DIMENSIONS];
		double * depthMapFacingPoly = new double[imageWidthFacingPoly*imageHeightFacingPoly];			//24bit to 3x8bit
 		unsigned char * rgbMapSmallFacingPoly = new unsigned char[smallImageWidth*smallImageHeight*RGB_NUM];	OR;
 		unsigned char * depthRGBMapSmallFacingPoly = new unsigned char[smallImageWidth*smallImageHeight];	//24bit to 3x8bit
		double * rgbDevIEnormalisedHueContrastMapSmallFacingPoly = new double[smallImageWidth*smallImageHeight*VEC_MAP_VEC_NUM_DIMENSIONS];
		*/


	#define OR_MYSQL_FIELD_NAME_BASICS_MAX_LENGTH (1*30 + 9*3)	//1*64bit + 9*8bit
	#define OR_MYSQL_FIELD_NAME_POINT_MAX_LENGTH (10 * 6 * 10)	//max 10 significant figures
	#define OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_MAX_DATA_LENGTH (1000 + OR_IMAGE_COMPARISON_SQL_BASICS_MAX_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_POINT_MAX_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_GEOMETRIC_COMPARISON_MAX_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_AVERAGE_RGB_DEV_BINNING_MAX_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_MAX_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_SMALL_HUE_DEV_MAP_COMPARISON_MAX_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE_MAX_DATA_LENGTH*2)
	#define OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_MAX_FIELD_DATA_LENGTH (1000 + OR_MYSQL_FIELD_NAME_BASICS_MAX_LENGTH + OR_MYSQL_FIELD_NAME_POINT_MAX_LENGTH + OR_MYSQL_FIELD_TYPE_GEO_BINS_MAX_LENGTH + OR_MYSQL_FIELD_NAME_DCT_COEFFICIENT_MAX_LENGTH + OR_MYSQL_FIELD_TYPE_COLOUR_AVERAGE_MAX_LENGTH + OR_MYSQL_FIELD_NAME_SMALL_IMAGE_MAX_LENGTH)
	//#define OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_INSERT_QUERY_MAX_LENGTH (OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_MAX_FIELD_DATA_LENGTH + OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_MAX_FIELD_DATA_LENGTH)
	//#define OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_GET_QUERY_MAX_LENGTH (OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_MAX_FIELD_DATA_LENGTH)
	#define OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_INSERT_QUERY_MAX_LENGTH (1000 + 1000 + OR_IMAGE_COMPARISON_SQL_ADD_ALL_MAPS_TO_DATABASE_MAX_DATA_LENGTH*2)	//x2 for escape characters
	#define OR_IMAGE_COMPARISON_SQL_DATABASE_TEST_AND_TRAIN_TABLES_GET_QUERY_MAX_LENGTH (1000)
#endif

#define OR_IMAGE_COMPARISON_SQL_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_JPG_DCT_BLOCK_SIZE (8)
//#define OR_METHOD3DOD_IMAGE_COMPARISON_COMPARE_DEPTH_MAPS	//not yet implemented
#define OR_IMAGE_COMPARISON_SQL_HUE_DEV_VAL_TO_8BIT_CONVERSION_MULTIPLIER (100.0)



	/**********
	OR TIME TEST VARIABLES;
	***********/

//#define TEST_VIEWTIME_SPEED_Z_FOR_WEBSITE
//#define TEST_VIEWTIME_SPEED_Z_FOR_WEBSITE_OLD_ADDITIONAL





	/**********
	OR LONG TERM DEBUG VARIABLES;
	***********/

	//debug only, but dont cause any issues being left on;
#define OR_METHOD_GEO_COMPARISON_RECORD_ORIGINAL_T_FOR_DEBUG


	/**********
	OR FEATURE ACCURACY VARIABLES;
	***********/

#define USE_RBB_QUADRATIC_FIT_KEYPOINT_GENERATION		//best accuracy
//#define USE_RBB_BASIC_KEYPOINT_GENERATION			//old inaccurate
//#define USE_HEITGER_ASCII_KEYPOINT_GENERATION			//old inaccurate


	/**********
	OR COMMON VARIABLES;
	***********/

#define OR_METHOD_POLYGON_NUMBER_OF_SIDES (3) //triangle



	/**********
	OR OLD PERFORMANCE FOR SPEED SACRIFICE VARIABLES - NOT USED
	***********/

	//3. optimisation: image comparison hue binning [will currently theoretically provides a small speed boost, but will limit OR to environments where lighting hue does not vary between train and test]
//#define OR_METHOD_DO_NOT_REQUIRE_TO_SUPPORT_LIGHTING_COLOUR_HUE_VARIATION
#ifdef OR_METHOD_DO_NOT_REQUIRE_TO_SUPPORT_LIGHTING_COLOUR_HUE_VARIATION
	//#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_BASIC_NO_SQL
	#ifdef OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_BASIC_NO_SQL		//currently only works with OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO [not OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO_V2]!!!!!!
		#define OR_METHOD_SMALL_IMAGE_FIRST_COMPARISON_NO_KERNEL
		#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_ALLOW_LIGHTING_COLOUR_SATURATION_VARIATION
		#ifdef OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_ALLOW_LIGHTING_COLOUR_SATURATION_VARIATION
			#define OR_IMAGE_COMPARISON_AVERAGE_RGB_BINNING_LIGHTING_COLOUR_SATURATION_VARIATION_VAL_PER_COL (10)
		#endif
	#endif
#endif






	/**********
	OR OPTIMISATION SMALL IMAGE COMPARISON VARIABLES
	***********/

#define OR_METHOD_USE_SMALL_IMAGE_FIRST_COMPARISON

#define OR_METHOD_USE_SMALL_IMAGE_RATIO_IGNORE_BG_COMPARISON_V2	//new
//#define OR_METHOD_USE_SPECIFIC_BG_COLOUR
#ifdef OR_METHOD_USE_SPECIFIC_BG_COLOUR
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_R (255)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_G (0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_B (255)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_R_NORM (1.0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_G_NORM (0.0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_B_NORM (1.0)
#else
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_R (0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_G (0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_B (0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_R_NORM (0.0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_G_NORM (0.0)
	#define OR_SNAPSHOT_BACKGROUND_COLOUR_B_NORM (0.0)
#endif



	/**********
	OR GEOMETRIC COMPARISON OPTIMISATIONS NOT YET IMPLEMENTED
	***********/

	//this optimisation probably will never be implemented;
//#define OR_GEOMETRIC_CHECK_COMPARISON_ERROR_DEV_CHECK	//not yet tested
	//#define OR_GEOMETRIC_CHECK_COMPARISON_ERROR_DEV (0.2)


	//this optimisation not yet tested;
//#define OR_METHOD_GEO_COMPARISON_DYNAMIC_ERROR_THRESHOLD
//#define OR_METHOD_GEO_COMPARISON_DYNAMIC_ERROR_THRESHOLD_MIN_EXPECTED_ORIG_TRI_WIDTH_OR_HEIGHT (10)	//in pixels






	/**********
	OR OPTIMISATION GEOMETRIC COMPARISON VARIABLES
	***********/

	//Geometric comparison enables increased execution speed x1000, but decreases redundancy slightly;
		//(NB if use 3DOD, require OR_METHOD_3DOD_USE_FORMAL_TRANSFORMATION_METHOD)

//#define TEMPTEST3GEOACCURACY	//debug only;

#define OR_METHOD_GEOMETRIC_COMPARISON
#ifdef OR_METHOD_GEOMETRIC_COMPARISON

	#define OR_METHOD_TRANSFORM_NEARBY_FEATURES_TAG_OT_FEATURES

	#ifdef OR_IMAGE_COMPARISON_SQL

	#else
		#ifndef OR_LOW_RAM
			#ifdef LINUX
				//NB V2 option currently does not work with windows compilation	due to array dec differences between vis c++ and g++
				#define OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO_V2	//was supposed to give higher performance than v1, but does not because nearest feature matching error is so high.. [possibly will work once feature detection has subpixel accuracy applied]
			#else
				#define OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO
			#endif
		#else
			#define OR_METHOD_GEOMETRIC_COMPARISON_NON_OPTIMISED_FILE_IO
		#endif
	#endif

	#ifdef OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO

	#elif defined OR_IMAGE_COMPARISON_NONSQL_GEOMETRIC_COMPARISON_OPTIMISED_TRAIN_FILE_IO_V2

		#define OR_METHOD_GEOMETRIC_COMPARISON_BINNING
		#define OR_IMAGE_COMPARISON_GEOMETRIC_COMPARISON_BINNING

	#elif defined OR_METHOD_GEOMETRIC_COMPARISON_NON_OPTIMISED_FILE_IO

	#elif defined TEMPTEST3GEOACCURACY
		//#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML_PRINT_OBJECT_NAMES

	#else
		//OR_IMAGE_COMPARISON_GEOMETRIC_COMPARISON_BINNING....

	#endif

	//#ifndef OR_METHOD_GEOMETRIC_COMPARISON_BINNING
		#define OR_GEOMETRIC_CHECK_MIN_NUMBER_PASSES (2)	//default; 2	//this is only used
	//#endif

#else

	//OLD;;
	/*
	#define OR_METHOD_NUM_NEARBY_FEATURES_TO_TRANSFORM (0)
	#ifdef OR_METHOD_ONLY_USE_ONE_POLY_PER_FEATURE_FAST_BUT_LOW_REDUNDANCY
		#define NUMBER_OF_POLYGONS_PER_FEATURE (1) 		//default; 1
	#else
		#define NUMBER_OF_POLYGONS_PER_FEATURE (3) 		//default; 3
	#endif
	*/
	/*
	#define OR_METHOD_GEOMETRIC_COMPARISON_USE_TEST_RGB_MAP_OPTIMISATION
	*/
#endif







	/**********
	OR OPTIMISATION VARIABLES2;
	***********/

//8. optimisation:  temp debug;
//#define DEBUG_ONLY_GENERATE_FEATURE_LISTS_NOTHING_ELSE

//9. optimisation: general;
#define OR_IMAGE_COMPARISON_USE_NEW_COMPARITOR	//test step 3
	#define OR_IMAGE_COMPARISON_DEBUG_NEW_COMPARITOR	//test step 3b
#define OR_USE_HEITGER_OBJECT_FEATURE_CALCULATION_CODE			//by default, use OR_USE_HEITGER_OBJECT_FEATURE_CALCULATION_CODE


//10. optimisation: memory
#ifndef OR_DEBUG_SAVE_REFERNCE_LIST_TO_FILE
#define OR_OPTIMISATION_DO_NOT_SAVE_REFERENCE_LIST_TO_FILE
#endif
#define OR_OPTIMISATION_DO_NOT_CREATE_UNNECESSARY_ARRAYS

//11. optimisation: hardware acceleration
#define USE_HARDWARE_ACCELERATION	//Default configuration is to use this!
#ifdef USE_HARDWARE_ACCELERATION
	#define RT_NO_TEXT_FEEDBACK
	#define USE_OPENGL		//must have freeglut installed
	#define USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS
	#define USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS_ADV

	//#define USE_OPENGL_OPTIMISED_TRIANGLE_RENDERING		//this is slower
#endif


//old versions;
//#define OR_METHOD_3DOD_USE_OLD_TESTED_BUT_BASIC_FEATURE_DETECTION	//not using this results in a problem, some features are off the object by 1 pixel;
	//#define DO_NOT_USE_CENTRE_PIXEL_REQ	//BAD







	/**********
	COMPILATION TYPE DEPENDENT VARIABLES;
	***********/


#ifdef COMPILE_CS
	#define USE_CS
	#define CS_USE_RAINBOW_COLOURS_FOR_FILE_BOXES		//optional
	//#define CS_USE_RAINBOW_COLOURS_FOR_FUNCTION_BOXES	//optional
	#define CS_DISPLAY_INCLUDE_FILE_PARSING
	#define CS_CENTRE_BOXES
	#define CS_DO_NOT_DRAW_ALL_FUNCTION_CONNECTIONS_WHEN_TRACING_A_BOTTOM_LEVEL_FUNCTION_UPWARDS
	//#define CS_DO_NOT_DRAW_ALL_FUNCTION_BOXES_AND_TEXT_WHEN_TRACING_A_BOTTOM_LEVEL_FUNCTION_UPWARDS
	//#define CS_DO_NOT_DRAW_ALL_FILE_CONNECTIONS_WHEN_TRACING_A_BOTTOM_LEVEL_FUNCTION_UPWARDS
	//#define CS_DO_NOT_DRAW_ALL_FILE_BOXES_AND_TEXT_WHEN_TRACING_A_BOTTOM_LEVEL_FUNCTION_UPWARDS
#endif
#ifdef USE_CS
	#define USE_RT
#endif


#ifdef COMPILE_OR
	#define USE_OR
#endif

#ifdef COMPILE_TH_OR_IMAGE_CATEGORISTION_NN
	#define USE_OR
	#define USE_ANN
#endif

#ifdef COMPILE_TH_OR_METHOD_2DOD
	#define USE_OR
#endif

#ifdef COMPILE_TH_OR_METHOD_3DOD
	#define USE_OR
	#define OR_METHOD3DOD_TEST
#endif
#ifdef COMPILE_TH_OR_METHOD_2DOD_WITH_ANN
	#define USE_ANN
	#define USE_OR
#endif
#ifdef COMPILE_TH_OR_METHOD_3DOD_WITH_ANN
	#define USE_ANN
	#define USE_OR
#endif
#ifdef USE_OR
	#define USE_RT
#endif


//#define OR_METHOD2DOD_GENERATE_IMAGE_DATA
#define OR_METHOD2DOD_USE_PREEXISTING_IMAGE_DATA
#ifdef OR_METHOD2DOD_USE_PREEXISTING_IMAGE_DATA
	#define OR_METHOD2DOD_TEST_ACROSS_MULTIPLE_VIEWS			//this scenario has not yet been coded properly for 3D method; need to work out appropriate camera coordinates for all view angles
	#define OR_METHOD2DOD_USE_SINGLE_OBJECT
	//#define OR_USE_STAR_MAPS
	#define OR_USE_AMSTERDAM_TEST_IMAGE_DATA
	//#define OR_USE_GOOGLE_MAPS
	#ifdef OR_USE_STAR_MAPS
		#define OR_USE_SINGLE_TRAIN_STAR_MAP
		//#define OR_DO_NOT_IGNORE_BACKGROUND_COLOUR
		#define OR_METHOD_2DOD_ASSUME_NO_3D_ROTATION
	#endif
	#ifdef OR_USE_GOOGLE_MAPS
		//#define OR_USE_CROPPED_GOOGLE_MAPS_FOR_BEST_CASE_SCENARIO_TEST	//temp

		//currently testing google map OR heitger feature calculation postprocessor code
		#define OR_USE_HEITGER_OBJECT_FEATURE_CALCULATION_POST_PROCESSOR 	//a post processor is required, but it has not yet been implemented - the post processor will eliminate all features which are not distinct features, thereby reducing total number of features
	#endif
#elif defined OR_METHOD2DOD_GENERATE_IMAGE_DATA
	#define OR_METHOD2DOD_USE_SINGLE_OBJECT
	//#define OR_METHOD2DOD_TEST_ACROSS_MULTIPLE_VIEWS		//this scenario has not yet been coded properly for 3D method; need to work out appropriate camera coordinates for all view angles
#endif
/*
#ifdef OR_USE_STAR_MAPS
	#define OR_METHOD2DOD_MINIMUM_AREA_OF_NORMALISATION_POLYGON (400)	//2500
#else

	#define OR_METHOD_SIDE_LENGTH_FOR_MINIMUM_SIDE_LENGTH_RATIO_OF_EQUILATERAL_T (20)
	#define OR_METHOD_MINIMUM_SIDE_LENGTH_RATIO_OF_EQUILATERAL_T (5) //ie the minimum allowed is a 4x1 sided triangle

#endif
*/



//#define OR_DEBUG_RAYTRACE_INTERPOLATED_3D_MAP_WITH_ORIGINAL_VIEW
#define OR_METHOD3DOD_GENERATE_IMAGE_DATA
#define OR_METHOD3DOD_USE_SINGLE_OBJECT
//untested;
//#define OR_METHOD3DOD_TEST_ACROSS_MULTIPLE_VIEWS
//#define OR_METHOD_ASSUME_TRAIN_AND_TEST_WITH_MULTI_VIEWPOINT_ADVANCED_VERSION	//required if more than 1 train viewpoint



#define IMAGEMAGIK_INSTALLED
#ifdef OR_USE_HEITGER_OBJECT_FEATURE_CALCULATION_CODE
	//#assert IMAGEMAGIK_INSTALLED
#endif
#ifdef OR_METHOD2DOD_USE_PREEXISTING_IMAGE_DATA
	//#assert IMAGEMAGIK_INSTALLED
#endif
//#ifdef OR_GENERATE_IMAGE_COMPARITOR_RESULTS_HTML
	//#assert IMAGEMAGIK_INSTALLED
//#endif
//#ifdef OR_METHOD_USE_SMALL_IMAGE_FIRST_COMPARISON
	//#assert IMAGEMAGIK_INSTALLED
//#endif


//OLD;
#ifdef OR_USE_OR_NEURAL_NETWORK_COMPARITOR
	#define OR_TEST_ORI_AND_POS_NOISE_DURING_TRANING_AND_TESTING
	#define OR_MANY_NUMBER_OF_OUTPUT_FILES
#endif

#ifdef COMPILE_ANN
	#define USE_ANN
	#define TH_USE_POVRAY_FOR_NEURAL_NETWORK_VEC_GRAPHICS
#endif

#ifdef COMPILE_ANN_WITH_RT
	#define USE_ANN
	#define TH_USE_RT_FOR_NEURAL_NETWORK_VEC_GRAPHICS
	#define USE_RT
#endif

#ifdef COMPILE_RT
	#define USE_RT
#endif

#ifdef COMPILE_TH_RT
	#define USE_RT
#endif



#ifdef COMPILE_LRRC
	#define USE_LRRC
#endif

#ifdef COMPILE_LRRC_WITH_ANN
	#define USE_LRRC
	#define USE_ANN
	#define USE_RT
#endif

#ifdef COMPILE_TH_ANN_WITH_LRRC
	#define USE_LRRC
	#define USE_ANN
	#define TH_USE_ANN_TEST_HARNESS
	#define USE_RT
#endif




#ifdef TH_USE_ANN_TEST_HARNESS

	//#define DEMONSTRATION_SCENARIO1		//combat/properties experience testing
	#define DEMONSTRATION_SCENARIO2			//object experience testing
	//#define DEMONSTRATION_SCENARIO3		//contains functions not yet tested


		//Primary variables been tested by TH;
	#ifdef DEMONSTRATION_SCENARIO1
		//#define TH_GAME_USE_OBJECT_RECOGNITION_EXPERIENCES
			//#define TH_USE_POVRAY_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
			//#define TH_USE_RT_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
		#define TH_LRRC_GAME_USE_CC_EXPERIENCES
		#define TH_LRRC_GAME_USE_LD_EXPERIENCES
		//#define TH_LRRC_GAME_USE_GLOBAL_EXPERIENCES
		#define TH_GAME_RAY_TRACE_NEURAL_NETWORK_VEC_GRAPHICS
			//#define TH_USE_POVRAY_FOR_NEURAL_NETWORK_VEC_GRAPHICS
			#define TH_USE_RT_FOR_NEURAL_NETWORK_VEC_GRAPHICS

	#elif defined DEMONSTRATION_SCENARIO2
		#define TH_GAME_USE_OBJECT_RECOGNITION_EXPERIENCES
			#define TH_USE_POVRAY_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
			//#define TH_USE_RT_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
		//#define TH_LRRC_GAME_USE_CC_EXPERIENCES
		//#define TH_LRRC_GAME_USE_LD_EXPERIENCES
		//#define TH_LRRC_GAME_USE_GLOBAL_EXPERIENCES
		#define TH_GAME_RAY_TRACE_NEURAL_NETWORK_VEC_GRAPHICS
			//#define TH_USE_POVRAY_FOR_NEURAL_NETWORK_VEC_GRAPHICS
			#define TH_USE_RT_FOR_NEURAL_NETWORK_VEC_GRAPHICS

	#elif defined DEMONSTRATION_SCENARIO3
		#define TH_GAME_USE_OBJECT_RECOGNITION_EXPERIENCES
			//#define TH_USE_POVRAY_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
			#define TH_USE_RT_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
		//#define TH_LRRC_GAME_USE_CC_EXPERIENCES
		//#define TH_LRRC_GAME_USE_LD_EXPERIENCES
		//#define TH_LRRC_GAME_USE_GLOBAL_EXPERIENCES
		#define TH_GAME_RAY_TRACE_NEURAL_NETWORK_VEC_GRAPHICS
			#define TH_USE_POVRAY_FOR_NEURAL_NETWORK_VEC_GRAPHICS - this should be enabled!@
			//#define TH_USE_RT_FOR_NEURAL_NETWORK_VEC_GRAPHICS

	#else
		//#define TH_GAME_USE_OBJECT_RECOGNITION_EXPERIENCES
			//#define TH_USE_POVRAY_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
			//#define TH_USE_RT_FOR_OBJECT_RECOGNITION_VEC_GRAPHICS
		#define TH_LRRC_GAME_USE_CC_EXPERIENCES
		#define TH_LRRC_GAME_USE_LD_EXPERIENCES
		//#define TH_LRRC_GAME_USE_GLOBAL_EXPERIENCES
		//#define TH_GAME_RAY_TRACE_NEURAL_NETWORK_VEC_GRAPHICS
			//#define TH_USE_POVRAY_FOR_NEURAL_NETWORK_VEC_GRAPHICS
			//#define TH_USE_RT_FOR_NEURAL_NETWORK_VEC_GRAPHICS

	#endif



	//#define TEST_LAYER_DIVERGENCE_TYPE_LINEAR_DIVERGING_THEN_CONVERGING	//Default=not yet decided upon



		//conditions required for TH
	#ifndef TH_LRRC_GAME_USE_GLOBAL_EXPERIENCES
		#define DEBUG_DO_NOT_USE_GLOBAL_EXPERIENCES
	#endif
	#define DEBUG_DO_NOT_PERFORM_KILL_RATIO_CHECKS_BEFORE_ADDING_UNIT_EXPERIENCES_TO_NN
	#define DEBUG_DO_NOT_DISPLAY_COMBAT_RESULTS
	#define DEBUG_STORE_EXPERIENCES_IN_PLAYER_NOT_UNITS
	#define DEBUG_HAVNT_YET_STARTED_TESTING_UNITGROUPS


		//variables no longer changed
	#ifndef DEMONSTRATION_SCENARIO1
		#define TH_LRRC_GAME_EMULATE_GAME_AI_REQUIREMENTS	//!! //Default=defined	[will use randomised distances if defined]
	#endif
		#define DEBUG_DO_NOT_USE_RANDOM_DICE_DURING_COMBAT


		//Old tests no longer changed
	//#define ANN_SEPARATE_CC_FROM_LD_NETWORK		//Default=not defined

	/*TEMP DEBUG PERIOD SHOULD NEVER BE REQUIRED AGAIN;
	//#define DEGDISREGARD_HIGH_ERROR_EXPERIENCES
		//TEMP!
		//#define TEMP_OUTPUT_HIGH_ERROR_EXPERIENCES
	*/

	/*LOW RAM ALGORITHM DOES NOT WORK YET;
	//#define TH_LRRC_LOW_RAM_AVAILABLE	//default= not defined
	#ifdef TH_LRRC_LOW_RAM_AVAILABLE
		#define TH_LRRC_LOW_RAM_NUM_CONSEC_TRAINING_EPOCHS_PER_EXPERIENCE 50
	#endif
	*/

#endif

	//Additional Debug Scenarios;

//#define DEBUG_DO_NOT_USE_ADVANCED_LEARNING_BASED_UPON_DISTANCES
#ifdef DEBUG_DO_NOT_USE_ADVANCED_LEARNING_BASED_UPON_DISTANCES
	#define DEBUG_DO_NOT_USE_GLOBAL_EXPERIENCES
#endif

#define ANN_USE_MIN_NUM_EPOCHS_BEFORE_DECLARE_OVERFITTING_DATA
#ifdef ANN_USE_MIN_NUM_EPOCHS_BEFORE_DECLARE_OVERFITTING_DATA
	#define ANN_MIN_NUM_EPOCHS_BEFORE_DECLARE_OVERFITTING_DATA (50)	//10
#endif

#ifdef TH_GAME_USE_OBJECT_RECOGNITION_EXPERIENCES
	#define DEBUG_ANN_OBJECT_RECOGNITION_EXPERIENCES_OUTPUT_ALL_MAPS
	#define USE_HI_RES_PRIMITIVE_REPLACEMENT_DURING_RENDERING
	//#define ANN_OBJECT_RECOGNITION_EXPERIENCES_RANDOMISE_LIGHTING_CONDITIONS	//not available yet

	//#define GAME_OBJECT_RECOGNITION_EXPERIENCE_FEED_RGB_MAP
	//#define GAME_OBJECT_RECOGNITION_EXPERIENCE_FEED_LUMINOSITY_MAP
	//#define GAME_OBJECT_RECOGNITION_EXPERIENCE_FEED_LUMINOSITY_BOOLEAN_MAP
	//#define GAME_OBJECT_RECOGNITION_EXPERIENCE_LUMINOSITY_CONTRAST_MAP
	#define GAME_OBJECT_RECOGNITION_EXPERIENCE_LUMINOSITY_CONTRAST_BOOLEAN_MAP	//DEFAULT
#endif


#define DEBUG_ANN_VERIFY_REAL_LIFE_ACCURACY_DIAGNOSTICS_CUTOFF
#ifdef DEBUG_ANN_VERIFY_REAL_LIFE_ACCURACY_DIAGNOSTICS_CUTOFF
	#define DEBUG_ANN_PERFORM_ALTERNATE_ERROR_TOTAL
#endif

//#define LRRC_GAME_DO_NOT_USE_FOLDS_DURING_1DNN_TRAINING





//Program Type variables



//Debug variables
#define DEBUG_PERFORM_ONLY_1_GAME
#define DEBUG_IN_TEXTPAD
//#define DEBUG_NO_UNITGROUP_AI



//#define DEBUG_DO_NOT_PERFORM_KILL_RATIO_CHECKS_BEFORE_ADDING_UNIT_EXPERIENCES_TO_NN
//#define DEBUG_NO_CREATIVITY_ALWAYS_PERFORM_COMBAT_WITH_LOWEST_ERROR_UNIT
//#define DEBUG_NO_CREATIVITY_ALWAYS_PERFORM_MOVEMENT_INSTEAD_OF_STAND_FOR_LDCOMBAT
//#define DEBUG_SPRITES
//#define DEBUG_AI_MOVE_UNIT
//#define DEBUG_ADD_INDIVIDUAL_SPRITES
//#define OR_DEBUG_METHOD_2DOD


//Test variables (need optimisation)
#define MAX_ANN_BACK_PROPAGATION_ERROR (1000.0)


#define CHAR_NEWLINE '\n'
#define CHAR_SPACE ' '


#endif

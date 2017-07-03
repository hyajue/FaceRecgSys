 
FaceDetect.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CFaceDetectApp application class.

FaceDetect.cpp
    This is the main application source file that contains the application
    class CFaceDetectApp.


/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

/////////////////////////////////////////////////////////////////////////////


FaceDetectDoc.h, FaceDetectDoc.cpp - the document
    These files contain CFaceDetectDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CFaceDetectDoc::Serialize).

FaceDetectView.h, FaceDetectView.cpp - the view of the document
    These files contain CFaceDetectView class.
    CFaceDetectView objects are used to view CFaceDetectDoc objects.



/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named FaceDetect.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.


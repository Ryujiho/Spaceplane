
// MFCApplication1View.cpp: CMFCApplication1View 클래스의 구현

#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1View
IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸
CMFCApplication1View::CMFCApplication1View() noexcept
{
	m_mouseMove = false;
	m_camera_x = 5.f;
	m_camera_y = 5.f;
}
CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 그리기
void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
	Invalidate(FALSE); //mouse move 후에 화면 업데이트 해준다.
}

// CMFCApplication1View 인쇄 
void CMFCApplication1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CMFCApplication1View 진단
#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}
void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG

// CMFCApplication1View 메시지 처리기
// SetPixelFormat
// desc: function to set the pixel format for the device context
//
BOOL CMFCApplication1View::SetDevicePixelFormat(HDC hdc)
{
	int pixelformat;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),		// size of this pfd
		1,									// default version
		PFD_DRAW_TO_WINDOW |				// support window
		PFD_SUPPORT_OPENGL |				// support opengl
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER,					// double buffered
		PFD_TYPE_RGBA,						// rgba type
		32,									// 32-bit color depth
		0, 0, 0, 0 ,0 ,0,					// color bits ignored
		8,									//no alpha buffer
		0,									//shift bit ignored
		8,									//no accumulation buffer
		0, 0, 0, 0,							//accum bits ignored
		16,									//16bit z-buffer
		0,									//no stencil buffer
		0,									//no auxiliary buffer
		PFD_MAIN_PLANE,						//main layer
		0,									//reserved
		0, 0, 0								//layer masks ignored
	};

	// choose best matching pixel format
	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE) {
		MessageBox(LPCTSTR("ChoosePixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}

	// set pixel format to device context
	if ((SetPixelFormat(hdc, pixelformat, &pfd)) == FALSE) {
		MessageBox(LPCTSTR("SetPixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}
	return true;
}

int CMFCApplication1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_hDC = GetDC()->m_hDC;

	//set the pixel format
	if (!SetDevicePixelFormat(m_hDC)) {
		return -1;
	}

	//create rendering context and make it current
	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hglRC);

	//initialize renderring mode
	InitGL();

	return 0;
}

void CMFCApplication1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_B836042.destroy();

	//deselect rendering context and delete it
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}

void CMFCApplication1View::InitGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	m_B836042.initialize();
}

void CMFCApplication1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReSizeGLScene(cx, cy);
}

// [3차시] Transformation 
void CMFCApplication1View::ReSizeGLScene(GLsizei width, GLsizei height)
{
	// don't want a divede by zero
	if (height == 0)
		height = 1;

	// reset the viewport to new dimensions
	glViewport(0, 0, width, height);  // 초기시점 ~ 전체 해상도
	glMatrixMode(GL_PROJECTION); //가시영역 
	glLoadIdentity();

	// calculate aspect ratio of the window (수직화각(0~180), x와 y비율, 최소 최대 볼 수 있는 거리 등)
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	// set modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void drawTwoLights() {
	GLfloat light_ambient[] = { 0.05, 0.2, 0.05, 1.0 };
	GLfloat light_diffuse[] = { 0.6, 0.8, 0.4, 1.0 };
	GLfloat light_specular[] = { 1, 1, 1, 1.0 };
	GLfloat light_position[] = { 0.2, 2.2, 5.0, 0.0 };//directional
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light1_ambient[] = { 0.1, 0.0, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 0.6, 0.2, 0.5, 1.0 };
	GLfloat light1_specular[] = { 1, 1, 1, 1.0 };
	GLfloat light1_position[] = { -1, -2, -3.0, 1.0 };//directional
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


	GLfloat light2_ambient[] = { 0.1, 0.0, 0.2, 1.0 };
	GLfloat light2_diffuse[] = { 0.6, 0.2, 0.5, 1.0 };
	GLfloat light2_specular[] = { 1, 1, 1, 1.0 };
	GLfloat light2_position[] = { -1, -2, 3.0, 1.0 };//directional
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

// 물체 등을 그리는 부분을 정의 - onDraw에서 호출
void CMFCApplication1View::DrawGLScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (!m_B836042.m_defaultMode) {
		GLfloat positionY = m_B836042.m_positionY;
		GLfloat positionZ = m_B836042.m_positionZ;
		GLfloat cameraX, cameraY, cameraZ;
		 cameraY = positionY; cameraZ = positionZ;

		if (m_B836042.m_isRight) {
			cameraZ += 2; cameraY += 1;
		}
		else if (m_B836042.m_isUp) {
			cameraY -= 2;
			cameraZ += 1;
		} else if (m_B836042.m_isDown) {
			cameraY += 2;
			cameraZ += 1;
		} else {
			cameraZ -= 2; cameraY += 1;
		}

		gluLookAt(0, cameraY, cameraZ,   0.f, positionY, positionZ,  0.f, 1.f, 0.f);
	}
	else {
		gluLookAt(m_camera_x, m_camera_y, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	}
	GLdouble angleX, angleY;
	if (m_mouseMove) {
		angleX = 1 * (m_mouseCurrentPoint.x - m_mouseAnchorPoint.x);
		angleY = 1 * (m_mouseCurrentPoint.y - m_mouseAnchorPoint.y);
		glRotatef(angleX, 0, 1, 0);
		glRotatef(angleY, 1, 0, 0);
	}

	//drawTwoLights();	m_Lab.draw_lab5();
	m_B836042.draw();

	

	SwapBuffers(m_hDC);
}

void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_mouseMove = true;
	m_mouseAnchorPoint = point;
	CView::OnLButtonDown(nFlags, point);
}
void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_mouseMove = false;
	CView::OnLButtonUp(nFlags, point);
}
void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	m_mouseCurrentPoint = point;
	
	CView::OnMouseMove(nFlags, point);
}
void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
		if (!m_B836042.m_defaultMode) {
			case VK_LEFT:
				m_camera_x -= 0.1;
				break;
			case VK_RIGHT:
				m_camera_x += 0.1;
				break;
			case VK_UP:
				m_camera_y -= 0.1;
				break;
			case VK_DOWN:
				m_camera_y += 0.1;
				break;
		}
	case VK_OEM_PLUS: case VK_ADD:
		m_B836042.m_airplane_speed += 0.1; // 나중에 기준 변경
		m_B836042.m_isMoved = false;
		break;
	case VK_OEM_MINUS: case VK_SUBTRACT:
		m_B836042.m_airplane_speed -= 0.1;
		m_B836042.m_isMoved = false;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCApplication1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//enter, back, space, esc 인지를 검사한다. 해당 문자들은 제대로된 ASCII코드가 될 수 없으므로 제외.
	if (nChar != VK_RETURN && nChar != VK_BACK && nChar != VK_ESCAPE) {
		if (nChar == 'a' || nChar == 'd' || nChar == 'w' || nChar == 's') {
			m_B836042.m_isLeft = m_B836042.m_isRight = m_B836042.m_isUp = m_B836042.m_isDown = false;
			m_B836042.m_isMoved = true;
		}

		switch (nChar) {
		case 'a': //좌 회전 후 이동
			m_B836042.m_countLeft++;
			m_B836042.m_isLeft = true;
			break;
		case 'd': // 우 
			m_B836042.m_countRight++;
			m_B836042.m_isRight = true;
			break;
		case 'w': // 위
			m_B836042.m_countUp++;
			m_B836042.m_isUp = true;
			break;
		case 's': //아래
			m_B836042.m_countDown++;
			m_B836042.m_isDown = true;
			break;

		case '1':	//디폴트 위치, 즉, +Z 방향에서 원점을 향해 보고 있는 시점
			m_B836042.m_defaultMode = true;
			m_camera_x = m_camera_y = 5.0f;
			break;

		case '2':	//비행체 뒤에서 따라 다니며(뒤에서, 그리고 약간 위에서)비행체 후면을 바라보는 시점
			m_B836042.m_defaultMode = false;
			break;
		}
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

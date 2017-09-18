#include "easy2d.h"
#include "EasyX\easyx.h"
#include <time.h>
#include <assert.h>
#include <imm.h>
#pragma comment(lib, "imm32.lib")
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


// App 的唯一实例
static App * s_pInstance = nullptr;
// 坐标原点的物理坐标
static int originX = 0;
static int originY = 0;

App::App() : 
	m_currentScene(nullptr), 
	m_nextScene(nullptr), 
	m_bRunning(false), 
	m_nWidth(0),
	m_nHeight(0),
	m_nWindowMode(0)
{
	assert(!s_pInstance);	// 不能同时存在两个 App 实例
	s_pInstance = this;		// 保存实例对象
	setFPS(60);				// 默认 FPS 为 60
}

App::~App()
{
	destory();				// 销毁 App
}

App * App::get()
{
	assert(s_pInstance);	// 断言实例存在
	return s_pInstance;		// 获取 App 的唯一实例
}

void App::setOrigin(int originX, int originY)
{
	::originX = originX;
	::originY = originY;
	setorigin(originX, originY);
}

int App::getOriginX()
{
	return ::originX;
}

int App::getOriginY()
{
	return ::originY;
}

int App::run()
{
	// 开启批量绘图
	BeginBatchDraw();
	// 修改时间精度
	timeBeginPeriod(1);
	// 获取 CPU 每秒滴答声个数
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	// 创建时间变量
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	// 记录当前时间
	QueryPerformanceCounter(&nLast);
	// 时间间隔
	LONGLONG interval = 0LL;
	// 挂起时长
	LONG waitMS = 0L;
	// 将隐藏的窗口显示
	ShowWindow(GetHWnd(), SW_NORMAL);
	// 运行游戏
	m_bRunning = true;

	// 进入主循环
	while (m_bRunning)
	{
		// 获取当前时间
		QueryPerformanceCounter(&nNow);
		// 计算时间间隔
		interval = nNow.QuadPart - nLast.QuadPart;
		// 判断间隔时间是否足够
		if (interval >= m_nAnimationInterval.QuadPart)
		{
			// 记录当前时间
			nLast.QuadPart = nNow.QuadPart;
			// 执行游戏逻辑
			_mainLoop();
		}
		else
		{
			// 计算挂起时长
			waitMS = LONG((m_nAnimationInterval.QuadPart - interval) * 1000LL / freq.QuadPart) - 1L;
			// 挂起线程，释放 CPU 占用
			if (waitMS > 1L)
				Sleep(waitMS);
		}
	}
	// 停止批量绘图
	EndBatchDraw();
	// 关闭窗口
	close();
	// 释放所有内存占用
	destory();
	// 重置时间精度
	timeEndPeriod(1);

	return 0;
}

void App::_initGraph()
{
	// 创建绘图环境
	initgraph(m_nWidth, m_nHeight, m_nWindowMode);
	// 隐藏当前窗口（防止在加载阶段显示黑窗口）
	ShowWindow(GetHWnd(), SW_HIDE);
	// 获取屏幕分辨率
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// 获取窗口大小
	CRect rcWindow;
	GetWindowRect(GetHWnd(), &rcWindow);
	// 设置窗口在屏幕居中
	SetWindowPos(GetHWnd(), HWND_TOP,
		(screenWidth - rcWindow.Size().cx) / 2,
		(screenHeight - rcWindow.Size().cy) / 2,
		rcWindow.Size().cx,
		rcWindow.Size().cy,
		SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOSIZE);
	// 禁用输入法
	ImmAssociateContext(GetHWnd(), NULL);
	// 重置绘图环境
	reset();
	// 设置窗口标题
	if (m_sTitle.empty())
	{
		// 保存当前标题
		TCHAR title[31];
		GetWindowText(GetHWnd(), title, 30);
		m_sTitle = title;
	}
	else
	{
		setWindowText(m_sTitle);
	}
}

void App::_mainLoop()
{
	// 下一场景指针不为空时，切换场景
	if (m_nextScene)
	{
		// 执行当前场景的 onExit 函数
		if (m_currentScene)
		{
			m_currentScene->onExit();
		}
		// 进入下一场景
		_enterNextScene();
		// 执行当前场景的 onEnter 函数
		m_currentScene->onEnter();
	}
	// 断言当前场景非空
	assert(m_currentScene);
	
	cleardevice();				// 清空画面
	m_currentScene->_onDraw();	// 绘制当前场景
	FlushBatchDraw();			// 刷新画面

	// 其他执行程序
	MouseMsg::__exec();			// 鼠标检测
	KeyMsg::__exec();			// 键盘按键检测
	Timer::__exec();			// 定时器执行程序
	FreePool::__flush();		// 刷新内存池
}

void App::createWindow(int width, int height, int mode)
{
	// 保存窗口信息
	m_nWidth = width;
	m_nHeight = height;
	m_nWindowMode = mode;
	// 创建窗口
	_initGraph();
}

void App::createWindow(tstring title, int width, int height, int mode)
{
	// 保存窗口信息
	m_nWidth = width;
	m_nHeight = height;
	m_nWindowMode = mode;
	m_sTitle = title;
	// 创建窗口
	_initGraph();
}

void App::setWindowSize(int width, int height)
{
	// 游戏正在运行时才允许修改窗口大小
	assert(m_bRunning);

	// 获取屏幕分辨率
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// 获取窗口大小（包含菜单栏）
	CRect rcWindow;
	GetWindowRect(GetHWnd(), &rcWindow);
	// 获取客户区大小
	CRect rcClient;
	GetClientRect(GetHWnd(), &rcClient);
	// 计算边框大小
	width += (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
	height += (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);
	// 销毁当前窗口
	// DestroyWindow(GetHWnd());/* 无法操作多线程导致失效 */
	// 修改窗口大小，并设置窗口在屏幕居中
	SetWindowPos(GetHWnd(), HWND_TOP,
		(screenWidth - width) / 2,
		(screenHeight - height) / 2,
		width,
		height,
		SWP_SHOWWINDOW);
	// 重置窗口属性
	reset();
}

void App::setWindowText(tstring title)
{
	// 设置窗口标题
	SetWindowText(GetHWnd(), title.c_str());
	// 保存当前标题，用于修改窗口大小时恢复标题
	m_sTitle = title;
}

void App::close()
{
	closegraph();	// 关闭绘图环境
}

void App::enterScene(Scene * scene, bool save)
{
	// 保存下一场景的指针
	m_nextScene = scene;
	// 切换场景时，是否保存当前场景
	m_bSaveScene = save;
}

void App::backScene()
{
	// 从栈顶取出场景指针，作为下一场景
	m_nextScene = m_sceneStack.top();
	// 不保存当前场景
	m_bSaveScene = false;
}

void App::clearScene()
{
	// 清空场景栈
	while (m_sceneStack.size())
	{
		auto temp = m_sceneStack.top();
		SAFE_DELETE(temp);
		m_sceneStack.pop();
	}
}

void App::setBkColor(COLORREF color)
{
	setbkcolor(color);
}

void App::_enterNextScene()
{
	// 若下一场景处于栈顶，说明正在返回上一场景
	if (m_sceneStack.size() && m_nextScene == m_sceneStack.top())
	{
		m_sceneStack.pop();					// 删除栈顶场景
	}
	
	if (m_bSaveScene)
	{
		m_sceneStack.push(m_currentScene);	// 若要保存当前场景，把它的指针放到栈顶
	}
	else
	{
		SAFE_DELETE(m_currentScene);		// 否则删除当前场景
	}
	
	m_currentScene = m_nextScene;			// 切换场景
	m_nextScene = nullptr;					// 下一场景置空
}

void App::quit()
{
	m_bRunning = false;
}

void App::end()
{
	m_bRunning = false;
}

void App::reset()
{
	// 重置绘图环境
	graphdefaults();
	setbkmode(TRANSPARENT);
	setbkcolor(Color::black);
}

Scene * App::getCurrentScene()
{
	// 获取当前场景的指针
	return m_currentScene;
}

LPCTSTR easy2d::App::getVersion()
{
	return _T("1.0.2");
}

void App::setFPS(DWORD fps)
{
	// 设置画面帧率，以毫秒为单位
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	m_nAnimationInterval.QuadPart = (LONGLONG)(1.0 / fps * nFreq.QuadPart);
}

int App::getWidth() const
{
	return m_nWidth;
}

int App::getHeight() const
{
	return m_nHeight;
}

void App::free()
{
	// 释放场景内存
	SAFE_DELETE(m_currentScene);
	SAFE_DELETE(m_nextScene);
	// 清空场景栈
	while (m_sceneStack.size())
	{
		auto temp = m_sceneStack.top();
		SAFE_DELETE(temp);
		m_sceneStack.pop();
	}
	// 删除所有定时器
	Timer::clearAllTimers();
}

void App::destory()
{
	// 释放所有内存
	free();
	// 实例指针置空
	s_pInstance = nullptr;
}

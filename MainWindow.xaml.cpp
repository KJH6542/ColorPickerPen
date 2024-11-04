#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CPPen::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

// CanvasControl 관련 네임스페이스
using namespace Microsoft::Graphics::Canvas::UI::Xaml;

// 색상 및 선 정보를 저장할 변수
struct winrt::Windows::UI::Color mYcol = winrt::Microsoft::UI::Colors::Green();

// 선 정보를 저장할 구조체
struct Line
{
    std::vector<winrt::Windows::Foundation::Point> points; // 선의 포인트
    winrt::Windows::UI::Color color; // 선의 색상
};

// 모든 선을 저장할 벡터
std::vector<Line> lines;

bool isDrawing = false; // 그리기 시작 여부
Line currentLine; // 현재 그려지는 선

// CanvasControl의 Draw 이벤트 처리
void winrt::CPPen::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();

    // 저장된 모든 선을 그립니다
    for (const auto& line : lines)
    {
        for (size_t i = 1; i < line.points.size(); ++i)
        {
            args.DrawingSession().DrawLine(line.points[i - 1], line.points[i], line.color, 4);
        }
    }

    // 현재 그려지고 있는 선을 그립니다
    for (size_t i = 1; i < currentLine.points.size(); ++i)
    {
        args.DrawingSession().DrawLine(currentLine.points[i - 1], currentLine.points[i], currentLine.color, 4);
    }
}

// 마우스 버튼이 눌렸을 때 처리
void winrt::CPPen::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    auto point = e.GetCurrentPoint(canvas).Position();

    // 새로운 선을 시작
    currentLine.points.clear(); // 현재 선의 포인트 초기화
    currentLine.color = mYcol; // 현재 선의 색상 설정
    currentLine.points.push_back(point); // 현재 포인트 추가
    isDrawing = true; // 그리기 시작
    canvas.Invalidate(); // 다시 그리기 요청
}

// 마우스가 이동할 때 처리
void winrt::CPPen::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    if (isDrawing) // 그리기 중일 때만 처리
    {
        CanvasControl canvas = sender.as<CanvasControl>();
        auto point = e.GetCurrentPoint(canvas).Position();

        // 현재 위치 추가
        currentLine.points.push_back(point); // 현재 위치 추가
        canvas.Invalidate(); // 다시 그리기 요청
    }
}

// 마우스 버튼을 놓았을 때 처리
void winrt::CPPen::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    if (isDrawing) // 그리기 중일 때만
    {
        lines.push_back(currentLine); // 현재 선을 저장
        isDrawing = false; // 그리기 종료
    }
}

// 색상 변경 이벤트 처리
void winrt::CPPen::implementation::MainWindow::myCol_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    mYcol = args.NewColor(); // 현재 색상 업데이트
}

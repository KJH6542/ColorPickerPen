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

// CanvasControl ���� ���ӽ����̽�
using namespace Microsoft::Graphics::Canvas::UI::Xaml;

// ���� �� �� ������ ������ ����
struct winrt::Windows::UI::Color mYcol = winrt::Microsoft::UI::Colors::Green();

// �� ������ ������ ����ü
struct Line
{
    std::vector<winrt::Windows::Foundation::Point> points; // ���� ����Ʈ
    winrt::Windows::UI::Color color; // ���� ����
};

// ��� ���� ������ ����
std::vector<Line> lines;

bool isDrawing = false; // �׸��� ���� ����
Line currentLine; // ���� �׷����� ��

// CanvasControl�� Draw �̺�Ʈ ó��
void winrt::CPPen::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();

    // ����� ��� ���� �׸��ϴ�
    for (const auto& line : lines)
    {
        for (size_t i = 1; i < line.points.size(); ++i)
        {
            args.DrawingSession().DrawLine(line.points[i - 1], line.points[i], line.color, 4);
        }
    }

    // ���� �׷����� �ִ� ���� �׸��ϴ�
    for (size_t i = 1; i < currentLine.points.size(); ++i)
    {
        args.DrawingSession().DrawLine(currentLine.points[i - 1], currentLine.points[i], currentLine.color, 4);
    }
}

// ���콺 ��ư�� ������ �� ó��
void winrt::CPPen::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    auto point = e.GetCurrentPoint(canvas).Position();

    // ���ο� ���� ����
    currentLine.points.clear(); // ���� ���� ����Ʈ �ʱ�ȭ
    currentLine.color = mYcol; // ���� ���� ���� ����
    currentLine.points.push_back(point); // ���� ����Ʈ �߰�
    isDrawing = true; // �׸��� ����
    canvas.Invalidate(); // �ٽ� �׸��� ��û
}

// ���콺�� �̵��� �� ó��
void winrt::CPPen::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    if (isDrawing) // �׸��� ���� ���� ó��
    {
        CanvasControl canvas = sender.as<CanvasControl>();
        auto point = e.GetCurrentPoint(canvas).Position();

        // ���� ��ġ �߰�
        currentLine.points.push_back(point); // ���� ��ġ �߰�
        canvas.Invalidate(); // �ٽ� �׸��� ��û
    }
}

// ���콺 ��ư�� ������ �� ó��
void winrt::CPPen::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    if (isDrawing) // �׸��� ���� ����
    {
        lines.push_back(currentLine); // ���� ���� ����
        isDrawing = false; // �׸��� ����
    }
}

// ���� ���� �̺�Ʈ ó��
void winrt::CPPen::implementation::MainWindow::myCol_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    mYcol = args.NewColor(); // ���� ���� ������Ʈ
}

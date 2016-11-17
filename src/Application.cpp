#include "../include/Application.h"

Application::Application(std::string title, int width, int height)
{
    this->title = title;
    this->width = width;
    this->height = height;
}

Application::~Application()
{
    delete p;
    delete m;
    delete g;

    glfwTerminate();
}

bool Application::Init()
{
    if (!glfwInit())
        return false;

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    g = new GPU();
    m = new Memory(g);
    p = new Processor(g, m);

    return true;
}

void Application::Loop()
{
    while (p->IsRunning() || !glfwWindowShouldClose(window))
    {

		p->C->SetByte(0, 0x00);
		p->D->SetByte(0, 0xFF);
		//p->SWAP(p->C);
		//p->ADD(p->C, p->D);
		//bool a = 0, b = 0, c = 1;
	

        Frame();
        this->g->Render();
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-1, -1);
        glVertex2f(0, 1);
        glVertex2f(1, -1);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::Frame()
{
    unsigned int fclk = this->p->tTotal + 70224;
    do
    {
        this->p->ProcessOpcode(this->p->FetchInstruction());
        this->p->Render();
    } while(this->p->tTotal < fclk);
}

int main(void)
{
    Application app("Test", 800, 600);

    if (!app.Init())
        return -1;

	

    app.Loop();

    return 0;
}

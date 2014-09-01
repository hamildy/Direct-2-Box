#include "game.h"

game::game()
{
	direct3d* direct3d_manage = NULL;
	object_manager* object_manage = NULL;
	input_manager* input_manage = NULL;
}

game::~game()
{
	if(object_manage != NULL)
	{
		delete object_manage;
		object_manage = NULL;
	}

	if(direct3d_manage != NULL)
	{
		delete direct3d_manage;
		direct3d_manage = NULL;
	}

	if(input_manage != NULL)
	{
		delete input_manage;
		input_manage = NULL;
	}
}

bool game::initialise(HWND window_handler, bool fullscreen, input_manager* input)
{
	//input = new input_manager(window_handler);
	input_manage = input;

	direct3d_manage = new direct3d();
	if(!direct3d_manage->initialise(window_handler, fullscreen))
	{
		return FALSE;
	}

	object_manage = new object_manager();

	return TRUE;
}

bool game::initialise_content()
{
	return TRUE;
}

void game::update(float timestamp)
{
	input_manage->begin_update();

	if(input_manage->get_key_down('E'))
	{
		trace("Test Trace: E pressed \n");
	}

	object_manage->update();

	input_manage->end_update();
}

void game::render()
{
	// Clear the screen to black.
	direct3d_manage->get_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// Tell Direct 3D to start drawing.
	if(SUCCEEDED(direct3d_manage->get_device->BeginScene()))
	{
		object_manage->render(direct3d_manage->get_device());

		// Done drawing for this scene.
		direct3d_manage->get_device->EndScene();
	}
	// Swap the old frame with the new one.
	direct3d_manage->get_device->Present(NULL, NULL, NULL, NULL);
}

void game::trace(const char * fmt, ...)
{
	char buffer[8192];
	va_list args;

	va_start(args, fmt);
	vsprintf(buffer, fmt, args);

	OutputDebugString(buffer);
}
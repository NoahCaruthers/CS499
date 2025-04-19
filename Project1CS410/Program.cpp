#include "Login.h"	
#include "MainForm.h"
#include "RegisterUserForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	User^ user = nullptr;
	while (true) {
		Project1CS410v2::Login loginForm;
		loginForm.ShowDialog();

		if (loginForm.switchToRegister) {
			Project1CS410v2::RegisterUserForm registerForm;
			registerForm.ShowDialog();

			if (registerForm.switchToLogin)
			{
				continue; // Go back to the login form
			}
			else {
				user = registerForm.user;
				break; // Exit the loop if registration is successful
			}
		}
		else {
			user = loginForm.user;

			if (user != nullptr)
			{
				Project1CS410v2::MainForm mainForm(user);
				Application::Run(% mainForm);
			}
			else
			{
				break;
			}
			
		}
	}
	return 0;
}
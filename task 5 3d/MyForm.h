#pragma once

namespace Yakunin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace std;

	vec3 Vc;
	vec3 V;
	vec3 Vc_work, V_work;
	mat4 T;
	mat4 initT;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	protected:


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(155, 120);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: float left = 30, right = 100, top = 20, bottom = 50;
			 float minX = left, maxX;
			 float minY = top, maxY;
			 float Wcx = left, Wcy;
			 float Wx, Wy;
			 float Wx_work, Wy_work;
			 float Wx_part = 0.6, Wy_part = 0.6;
			 float Wcx_work, Wcy_work;
			 float Wz_work;
			 int numXsect = 5, numYsect = 5, numZsect = 5;

	private: System::Void rectCalc() {
		maxX = ClientRectangle.Width - right;
		maxY = ClientRectangle.Height - bottom;
		Wcy = maxY;
		Wx = maxX - left;
		Wy = maxY - top;

		Wx_work = Wx_part * Wx;
		Wy_work = Wy_part * Wy;
		Wcx_work = maxX - Wx_work;
		Wcy_work = minY + Wy_work;
		Wz_work = Wcy - Wcy_work;
	}

	private:System::Void worldRectCalc() {
		Vc_work = normalize(T*vec4(Vc, 1.f));
		V_work = mat3(T) * V;
	}

	private: float f(float x, float z) {
		return x*sin(sqrtf(x*x+z*z));
	}

	private: bool f_exists(float x, float z, float delta) {
		return true;
	}
	
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

		Graphics^ g = e->Graphics;
		g->Clear(Color::Aquamarine);

		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen, left, top, Wx, Wy);

		Pen^ gridPen = gcnew Pen(Color::Black, 1);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
		



		//*****************************************************************************************
		float gridStep_y = Wy_work / numYsect;
		for (int i = 0; i <= numYsect; i++) {
			float tmpYCoord_g = Wcy_work - i * gridStep_y;
			g->DrawLine(gridPen, Wcx_work, tmpYCoord_g, maxX, tmpYCoord_g);
		}
		
		float gridStep_x = Wx_work / numXsect;
		for (int i = 0; i <= numXsect; i++) {
			float tmpYCoord_v = Wcy - i * gridStep_y;
			float tmpYCoord_g = Wcy_work - i * gridStep_y;
			g->DrawLine(gridPen, Wcx, tmpYCoord_v, Wcx_work, tmpYCoord_g);
		}
		float grid_dY = V_work.y / numYsect;
		float tick_y = Vc_work.y;
		for (int i = 0; i <= numYsect; i++) {
			float tmpYCoord_g = Wcy_work - i * gridStep_y;
			if (i > 0 && i < numYsect)
			g->DrawString(tick_y.ToString("F4"), drawFont, drawBrush, maxX, tmpYCoord_g);
			tick_y += grid_dY;
		}
		
		//******************************************************************************************






		//координатная сетка по оси x
		gridStep_x = Wx_work / numXsect;
		float grid_dX = V_work.x / numXsect;
		float tick_x = Vc_work.x;
		for (int i = 0; i <= numXsect; i++) {

			float tmpXCoord_d = Wcx + i * gridStep_x;
			float tmpXCoord_v = Wcx_work + i * gridStep_x;
			  g->DrawLine(gridPen, tmpXCoord_d, Wcy, tmpXCoord_v, Wcy_work);
			  g->DrawLine(gridPen, tmpXCoord_v, Wcy_work, tmpXCoord_v, minY);

			if (i > 0 && i < numXsect)
			  g->DrawString(tick_x.ToString("F4"), drawFont, drawBrush, tmpXCoord_d, Wcy);
		
			tick_x += grid_dX;
		}
		
		//координатная сетка по оси z
		gridStep_x = (Wx - Wx_work) / numZsect;
		gridStep_y = Wz_work / numZsect;
		float grid_dZ = V_work.z / numZsect;

		float tick_z = Vc_work.z;
		for (int i = 0; i <= numZsect; i++) {

			float tmpXCoord_v = Wcx_work - i * gridStep_x;
			float tmpYCoord_g = Wcy_work + i * gridStep_y;
			float tmpXCoord_g = tmpXCoord_v + Wx_work;

			  g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_v, tmpYCoord_g - Wy_work);
			  g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_g, tmpYCoord_g);

			if (i > 0 && i < numZsect)
			  g->DrawString(tick_z.ToString("F4"), drawFont, drawBrush, tmpXCoord_g, tmpYCoord_g);

			tick_z += grid_dZ;
		}
		










			   		 	  	  	   	
		Pen^ pen = gcnew Pen(Color::Blue, 1);
		float deltaX = V_work.x / Wx_work;
		float deltaZ = V_work.z / Wz_work;
		float deltaWcx = (Wcx_work - Wcx) / Wz_work;

		bool hasStart;

		float z = Vc_work.z;

		float Wcx_w = Wcx_work, Wcy_w = Wcy_work;
		while (Wcy_w <= Wcy) {

		vec2 start, end;
		float x, y;
		start.x = Wcx_w;
		x = Vc_work.x;
		hasStart = f_exists(x, z, deltaX);
		if (hasStart) {
			y = f(x,z);
			start.y = Wcy_w - (y - Vc_work.y) / V_work.y * Wy_work;
		}
			
		float maxX = Wcx_w + Wx_work;
		while (start.x < maxX) {
			
			vec2 end;
			bool hasEnd;
			float deltaY;
			float red, green, blue;
			end.x = start.x + 1.f;
			x += deltaX;
						
			hasEnd = f_exists(x, z, deltaX);
			if (hasEnd) {
				y = f(x,z);
				deltaY = (y - Vc_work.y) / V_work.y;
				end.y = Wcy_w - deltaY * Wy_work;
			}
						
			vec2 tmpEnd = end;
			bool visible = hasStart && hasEnd && clip(start, end, minX, minY, maxX, maxY);
			if (visible) {
				if (deltaY > 1.f) deltaY = 1.f;
				if (deltaY < 0.f) deltaY = 0.f;
				green = 510.f * deltaY;
				if (deltaY < 0.5f) {
					blue = 255.f - green;
					red = 0.f;
				}
				else {
					blue = 0.f;
					red = green - 255.f;
					green = 510.f - green;
				}
				pen->Color = Color::FromArgb(red, green, blue);
				g->DrawLine(pen, start.x, start.y, end.x, end.y);
			}
			start = tmpEnd;
			hasStart = hasEnd;
		}
		
		Wcy_w += 1.f;
		Wcx_w -= deltaWcx;
		z += deltaZ;
		}
	}
	
	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		rectCalc();
		Refresh();
	}
	
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		
		Vc = vec3(-2.f, -2.f, -2.f);
		V = vec3(4.f, 4.f, 4.f);

		initT = mat4(1.f);
		T = initT;

		rectCalc();
		worldRectCalc();
	}
	
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		
		float centerX = Vc_work.x + V_work.x / 2;
		float centerY = Vc_work.y + V_work.y / 2;
		float centerZ = Vc_work.z + V_work.z / 2;

		switch (e->KeyCode)	{

		case Keys::A:
			T = translate(-V_work.x / Wx, 0.f, 0.f) * T;
			break;

		case Keys::Z:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(1.1, 1.1, 1.1) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;

		case Keys::Escape:
			T = initT;
			break;

		case Keys::D:
			T = translate(V_work.x / Wx, 0.f, 0.f) * T;
			break;
		case Keys::W:
			T = translate(0.f, -V_work.y / Wy, 0.f) * T;
			break;
		case Keys::S:
			T = translate(0.f, V_work.y / Wy, 0.f) * T;
			break;
		case Keys::R:
			T = translate(0.f, 0.f, -1.1) * T;
			break;
		case Keys::F:
			T = translate(0.f, 0.f, 1.1) * T;
			break;
		case Keys::X:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(0.9, 0.9, 0.9) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;






		case Keys::Q:
			

			Wy_work = Wy_work * 0.9;
			

			break;
		case Keys::E:
			Wy_work = Wy_work * 1.1;
			break;
		case Keys::C:
			Wx_work = Wx_work * 0.9;
			break;
		case Keys::V:
			//Wx = Wx*0.9;
			Wx_work = Wx_work * 1.1;//(Wy_part * Wy)*0.9;
			//rectCalc()
			break;


		case Keys::T:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(1.1, 1.f, 1.f) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;
		case Keys::G:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(0.9, 1.f, 1.f) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;
		case Keys::Y:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(1.f, 1.1, 1.f) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;
		case Keys::H:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(1.f, 0.9, 1.f) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;
		case Keys::U:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(1.f, 1.f, 1.1) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;
		case Keys::J:
			T = translate(-centerX, -centerY, -centerZ) * T;
			T = scale(1.f, 1.f, 0.9) * T;
			T = translate(centerX, centerY, centerZ) * T;
			break;


		case Keys::O:
			numXsect++, numYsect++, numZsect++;
			break;
		case Keys::L:
			numXsect--, numYsect--, numZsect--;
			break;



			






		default:
			break;
		}
		worldRectCalc();
		Refresh();
	}
	
};
}

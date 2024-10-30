//Su dung toan tu cin va cout 
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<stdlib.h>
#include <iomanip>
#include <iostream>
using namespace  std;

#define MAX_TEN		50
#define MAX_MASO	10
#define LCB     1800000 

//Class Nhanvien
class NhanVien
{	protected: //private:
		char HoTen[MAX_TEN];
		char MaSo[MAX_MASO];
		float  Luong;
	public:
		NhanVien();
		virtual void TinhLuong()=0; 
		virtual void Xuat(); 
		virtual void Nhap();
		float getLuong();
		
		//...bo sung code
};

	
//Class Bien che
class BienChe: public NhanVien
{	protected: //private:
		float HeSoLuong;
		float HeSoPhuCap;
	public:
		BienChe();
		void TinhLuong();
		void Nhap();
		void Xuat();
};

//Dinh nghia lop HopDong
class HopDong : public NhanVien
{	protected: //private:
		float TienCong; // 1 ngay
		float NgayCong; // lon hon 24 ngay thi tinh 1.2
	public:
		HopDong();
		void TinhLuong();
		void Nhap();
		void Xuat();
};

void lk_LuongLonHon5tr(NhanVien *Nv[],int n);

int main()
{
	NhanVien *Nv[100];	int N=0;
	char Chon,Loai;
	float TongLuong=0, TBCLuong=0;
	cout<<"Nhap thong tin cho cac Nhan vien"<<endl;
	do
	{	cout<<"Bien che hay Hop dong (B/H)? ";
		cin>>Loai; 	Loai=toupper(Loai);
		if (Loai=='B')
			Nv[N]=new BienChe;
		else
			Nv[N]=new HopDong;
		Nv[N++]->Nhap();
		cout<<"Tiep tuc (C/K)? ";	cin>>Chon;
		Chon=toupper(Chon);
		if ((N==100)||(Chon=='K'))
			break;
	}
	while (1);
	cout<<"Thong tin cua cac nhan vien vua nhap"<<endl;
	for(int i=0;i<N;i++) Nv[i]->Xuat();
	for(int i=0;i<N;i++) TongLuong+=Nv[i]->getLuong();
	cout<<"\nTong luong cac nhan vien trong danh sach: "<<TongLuong;
	TBCLuong=TongLuong/N;
	cout<<"\nTrung binh cong luong cac nhan vien trong danh sach: "<<TBCLuong;
	cout<<"\nDanh sach nhan vien co luong lon hon 5.000.000:\n";
	lk_LuongLonHon5tr(Nv,N);
	getch();
	return 1;
}


//Dinh nghia ham thanh vien cho lop NhanVien
NhanVien::NhanVien()
{
	strcpy(HoTen,""); 
	strcpy(MaSo,"");
	Luong=0.0;
}

void NhanVien::Nhap()
{
	cout<<"Ma so:";	cin>>MaSo;
	cin.ignore(); //xoa dau Enter trong buffer
	cout<<"Ho va ten:"; 
	cin.getline(HoTen,MAX_TEN);
	//cin>>HoTen;
}

void NhanVien::Xuat() 
{	cout<<setiosflags(ios::fixed)<<setprecision(2);
	cout<<"[Ma so: "<<MaSo<<",Ho va ten: "<<HoTen
		 <<",Luong: "<<Luong;
}

float NhanVien::getLuong(){
	return Luong;
}

//Dinh nghia ham thanh vien cho lop BienChe
BienChe::BienChe()
{
	HeSoLuong=HeSoPhuCap=0;
}

void BienChe::Nhap()
{	
	NhanVien::Nhap();
	cout<<"He so luong: ";
	cin>>HeSoLuong;
	while(HeSoLuong<3 || HeSoLuong>14)
	{
		cout<<"He so luong phai tu 3.0 den 14.0! VUI LONG NHAP LAI!!!";
		cin>>HeSoLuong;
	};
	cout<<"Phu cap chuc vu: ";
	cin>>HeSoPhuCap;
	while(HeSoPhuCap<0.0 || HeSoPhuCap>2.0)
	{
		cout<<"Phu cap chuc vu phai tu 0.0 den 2.0! VUI LONG NHAP LAI!!!";
		cin>>HeSoPhuCap;
	};
	TinhLuong();
}

void BienChe::Xuat(){
	NhanVien::Xuat();
	cout<<", He so luong: "<<HeSoLuong<<", Phu cap chuc vu: "<<HeSoPhuCap<<"]\n";
}

void BienChe::TinhLuong()
{
	Luong=LCB*(HeSoLuong+HeSoPhuCap);
}

//Cac ham thanh vien trong lop HopDong
HopDong::HopDong()
{
	TienCong=NgayCong=0;
}

void HopDong::Nhap()
{
	NhanVien::Nhap();
	cout<<"Tien cong trong 1 ngay: ";
	cin>>TienCong;
	while(TienCong<100000 || TienCong>200000)
	{
		cout<<"Tien cong 1 ngay phai tu 100.000-200.000/ngay! VUI LONG NHAP LAI!!!";
		cin>>TienCong;
	};
	cout<<"So ngay lam viec trong 1 thang: ";
	cin>>NgayCong;
	while(NgayCong<0 || NgayCong>31)
	{
		cout<<"So ngay lam viec trong thang khong duoc duoi 0 va tren 31! VUI LONG NHAP LAI!!!";
		cin>>NgayCong;
	};
	if(NgayCong>24){
		float NgayVuot=NgayCong-24;
		NgayCong=24+(NgayVuot*1.2);
	};
	TinhLuong();
}

void HopDong::Xuat(){
	NhanVien::Xuat();
	cout<<", Tien cong: "<<TienCong<<", So ngay lam viec trong thang: "<<NgayCong<<"]\n";
}

void HopDong::TinhLuong()
{
	Luong=TienCong*NgayCong;
}

void lk_LuongLonHon5tr(NhanVien *Nv[],int n){
	for(int i=0;i<n;i++){
		if(Nv[i]-> getLuong() > 5000000) Nv[i]->Xuat();
	}
}


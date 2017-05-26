#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;
char gettime(){
	time_t rawtime;
	struct tm *info;
	char buffer[50];

	time(&rawtime);

	info = localtime(&rawtime);

	strftime(buffer, 80, "%x - %I:%M%p", info);
	return buffer[50];
}
class ThongBao{
public:
	int IDthongbao;
	int IDgui;
	int IDnhan;
	char time[50];
	char tieude[100];
	char noidung[1000];
	void ghi(fstream&);
	void doc(fstream&);
	void nhap();
};
void ThongBao::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(ThongBao));
}
void ThongBao::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(ThongBao));
}
void ThongBao::nhap() {
	cout << "Nhap ID nguoi nhan: "; cin >> IDnhan; cin.ignore();
	cout << "Nhap tieu de(<100 ky tu): "; cin.getline(tieude, 100);
	cout << "Nhap noi dung(<1000 ky tu): "; cin.getline(noidung, 100);
};
class Sach{
public:
	int ID;
	char tensach[30];
	char tentacgia[30];
	char ngonngu[20];
	char theloai[20];
	bool trangthai = 1;//chua muon
	float danhgia = 0; // thang 10, bang tong diem danh gia chia so luot danh gia;
	void doc(fstream&);
	void ghi(fstream&);
	void nhap();
};
void Sach::nhap() {
	cout << "Nhap ma so Sach: "; cin >> ID; cin.ignore();
	cout << "Nhap ten sach: "; cin.getline(tensach, 30);
	cout << "Nhap ten tac gia: "; cin.getline(tentacgia, 30);
	cout << "Ngon ngu: "; cin.getline(ngonngu, 20);
	cout << "The loai: "; cin.getline(theloai, 20);
};
void Sach::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(Sach));
}
void Sach::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(Sach));
}
class MuonSach :public Sach{
public:
	int ID;
	int IDsach;
	char tensach[30];
	char tentacgia[30];
	char ngonngu[20];
	char theloai[20];
	bool trangthai = 1;//chua muon
	float danhgia = 0; // thang 10, bang tong diem danh gia chia so luot danh gia;
	
	int IDmuon;
	char ngMuon[30];
	int ngayMuon[3]; // dinh dang ngay thang nam.
	int thoigian[3]; //dinh dang gio phu giay
	int ngayTra[3];
	void doc(fstream&);
	void ghi(fstream&);
};
void MuonSach::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(MuonSach));
}
void MuonSach::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(MuonSach));
}
class NguoiDung {
private:
public:
	char MasoNguoiDung[5];
	int sCMND;
	char tenNguoiDung[30];
	char ngaySinh[15];
	char diaChi[50];
	char tenDangNhap[30];
	char MatKhau[20];
	bool trangThai = 1;
	int chucVu;
	int dem = 0;
	void doc(fstream&);
	void ghi(fstream&);
	void nhap();
};
void NguoiDung::nhap() {
	cout << "Nhap ma so CMND: "; cin >> sCMND; cin.ignore();
	cout << "Nhap ho ten: "; cin.getline(tenNguoiDung, 30);
	cout << "Nhap ngay sinh: "; cin.getline(ngaySinh, 12);
	cout << "Nhap dia chi: "; cin.getline(diaChi, 20);
	cout << "Nhap ten Tai khoan: "; cin.getline(tenDangNhap, 30);
	cout << "Nhap Mat khau: "; cin.getline(MatKhau, 20);
	cout << "Nhap ma Chuc Vu: "; cin >> chucVu;
};
void NguoiDung::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(NguoiDung));
}
void NguoiDung::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(NguoiDung));
}
class Quyen {
public:
	unsigned int stt;
	bool DocGia = 0;
	bool ThuThu = 0;
	bool Admin = 0;
	char tenQuyen[100];
	void doc(fstream&);
	void ghi(fstream&);
};
void Quyen::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(NguoiDung));
}
void Quyen::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(NguoiDung));
}
int TruyXuatNgDung(NguoiDung v[]) {
	fstream inFile("UserData.DAT", ios::in);
	int dem = 0;
	while (!inFile.eof()) {
		v[dem].doc(inFile);
		dem++;
	}
	/*
	for (int i=0; i<dem-1; i++){
	cout << "sCMND: " << v[i].sCMND << endl;
	cout << "tenNguoiDung: " << v[i].tenNguoiDung << endl;
	cout << "ngaySinh: " << v[i].ngaySinh << endl;
	cout << "diaChi: " << v[i].diaChi << endl;
	cout << "Ten Tai khoan: " << v[i].tenDangNhap <<endl;
	cout << "Chuc vu: ";
	if (v[i].chucVu == 1) cout << "Administration" <<endl;
	else if (v[i].chucVu == 2) cout << "Thu Thu" << endl;
	else cout << "Doc Gia" << endl;
	}
	*/
	inFile.close();
	return dem - 1;
}
int TruyXuatSach(Sach v[]) {
	fstream inFile("Sach.DAT", ios::in);
	int dem = 0;
	while (!inFile.eof()) {
		v[dem].doc(inFile);
		dem++;
	}
	inFile.close();
	return dem - 1;
}
int TruyXuatMuonSach(MuonSach v[]) {
	fstream inFile("MuonSach.DAT", ios::in);
	int dem = 0;
	while (!inFile.eof()) {
		v[dem].doc(inFile);
		dem++;
	}
	inFile.close();
	return dem - 1;
}
int TruyXuatThongBao(ThongBao v[]) {
	fstream inFile("ThongBao.DAT", ios::in);
	int dem = 0;
	while (!inFile.eof()) {
		v[dem].doc(inFile);
		dem++;
	}
	inFile.close();
	return dem - 1;
}
void CapNhatNgDung(NguoiDung v[]) {
	int m;
	fstream outFile("UserData.DAT", ios::app);
	cout << "Nhap so luong:"; cin >> m;
	for (int i = 0; i<m; i++) {
		cout << "Nhap Du lieu Nguoi thu " << i + 1 << " :" << endl;
		v[i].nhap();
		v[i].ghi(outFile);
		cout << endl;
	}
	outFile.close();
}
void CapNhatSach(Sach s[]) {
	int m;
	fstream outFile("Sach.DAT", ios::app);
	cout << "Nhap so luong:"; cin >> m; cin.ignore();
	for (int i = 0; i<m; i++) {
		cout << "Nhap Du lieu Sach thu " << i + 1 << " :" << endl;
		s[i].nhap();
		s[i].ghi(outFile);
		cout << endl;
	}
	outFile.close();
}
void inmk(char pw[20]){
	int pas = 0;
	char c;
	while (c = getch()) {
		if (c == '\n' || c == '\r') {
			cout << "\n";
			break;
		}
		else if (c == '\b') {
			cout << "\b \b"; pas--;
		}
		else {
			cout << '*';
			pw[pas] = c;
			pas++;
		}
	}
	for (int i = (pas); i < 20; i++)pw[i] = '\0';
}
int timkiemchuoi(char a[], char b[]){
	char c[100], d[100];
	char *ret;
	strlwr(strcpy(c, a));
	strlwr(strcpy(d, b));

	ret = strstr(c, d);
	if (ret == NULL) return 0;
	else return 1;
}
void ThongBaoTuDong(NguoiDung ngDung[], int hientai, ThongBao thongbao[], int ms, MuonSach muonsach[]){
	int sl = TruyXuatThongBao(thongbao);
	int m = TruyXuatNgDung(ngDung);
	int sls = TruyXuatMuonSach(muonsach);
	//thongbao[sl].IDgui = ngDung[hientai].chucVu;
	thongbao[sl].IDthongbao = sl + 1;
	//thongbao[sl].nhap();
	time_t rawtime;
	struct tm *info;
	char buffer[50];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%x - %I:%M%p", info);
	strcpy(thongbao[sl].time, buffer);
	thongbao[sl].IDgui == -1;
	if (ms == 1){  // thong bao chao mung
		thongbao[sl].IDnhan = ngDung[m-1].sCMND;
		strcpy(thongbao[sl].tieude, "Chao mung ban den voi thu vien cua chung toi");
		strcpy(thongbao[sl].noidung, "Xin chao ");
		strcat(thongbao[sl].noidung, ngDung[m - 1].tenNguoiDung);
		strcat(thongbao[sl].noidung, ". Chung toi rat vui vi ban da den thu vien cua chung toi. Neu co bat ky thac mac nao xin hay lien he voi thu thu de duoc ho tro");
	}
	else if (ms == 2){ // thong bao muon sach thanh cong
		thongbao[sl].IDnhan = ngDung[hientai].sCMND;
		strcpy(thongbao[sl].tieude, "Muon sach thanh cong!");
		strcpy(thongbao[sl].noidung, "Chuc mung ban da muon thanh cong sach ");
		strcat(strcat(strcat(thongbao[sl].noidung, muonsach[sls - 1].tensach), " vao luc "), buffer);
		
		strcat(thongbao[sl].noidung, ". Ban phai tra sach muon nhat la sau 15 ngay ke tu ngay muon sach. Xin cam on. ");
	}
	else if (ms == 3){ // thong bao tra sach thanh cong
		thongbao[sl].IDnhan = ngDung[hientai].sCMND;
		strcpy(thongbao[sl].tieude, "Tra sach thanh cong!");
		strcpy(thongbao[sl].noidung, "Ban da tra thanh cong sach ");
		strcat(strcat(strcat(thongbao[sl].noidung, muonsach[sls - 1].tensach), " vao luc "), buffer);
		strcat(thongbao[sl].noidung, ". Cam on ban da tuog tac voi thu vien cua chung toi. ");
	}
	else if (ms == 4){  // thong bao Doi mat khau
		thongbao[sl].IDnhan = ngDung[m - 1].sCMND;
		strcpy(thongbao[sl].tieude, "Thong bao doi mat khau");
		strcpy(thongbao[sl].noidung, "Xin chao ");
		strcat(thongbao[sl].noidung, ngDung[m - 1].tenNguoiDung);
		strcat(thongbao[sl].noidung, ". De nghi ban doi mat khau trong lan dang nhap dau tien. Moi thac mac xin lien he admin.");
	}
	else cout << "";
	fstream outFile("ThongBao.DAT", ios::app);
	thongbao[sl].ghi(outFile);
	outFile.close();
}
int Chucnang(int hientai, NguoiDung ngDung[], int quyen, int &m, Quyen q[], char tdn[], Sach sach[], MuonSach muonsach[], ThongBao thongbao[]) {

	//#######Quyen 0. Them Nguoi dung#######################################################

	if (quyen == 0) {
		system("cls");
		CapNhatNgDung(ngDung);
		m = TruyXuatNgDung(ngDung);
		cout << "Them hoan tat!" << endl;
		ThongBaoTuDong(ngDung, hientai, thongbao, 1, muonsach);
		ThongBaoTuDong(ngDung, hientai, thongbao, 4, muonsach);

		Sleep(1311);
	}

	//#######Quyen 1. Khoa nguoi dung#######################################################

	else if (quyen == 1) {
		system("cls");
		int cm;
		int i;
		int tt = 0;
		cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
		for (i = 0; i < m; i++) {
			if (cm == ngDung[i].sCMND) {
				ngDung[i].trangThai = 0;
				cout << "\n";
				cout << "Khoa thanh cong!" << endl;
				tt = 1;
			}
		}
		fstream outFile("UserData.DAT", ios::out);
		for (int k = 0; k < m; k++){
			ngDung[k].ghi(outFile);
		}
		if (tt == 0) cout << "Khong tim thay nguoi nay!" << endl;
		outFile.close();
		Sleep(1311);
	}

	//#######Quyen 2. Mo Khoa nguoi dung#######################################################

	else if (quyen == 2) {
		system("cls");
		int cm;
		int i;
		int tt = 0;
		cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
		for (i = 0; i < m; i++) {
			if (cm == ngDung[i].sCMND) {
				ngDung[i].trangThai = 1;
				cout << "Mo Khoa thanh cong!" << endl;
				tt = 1;
			}
		}
		fstream outFile("UserData.DAT", ios::out);
		for (int k = 0; k < m; k++){
			ngDung[k].ghi(outFile);
		}
		if (tt == 0) cout << "Khong tim thay nguoi nay!" << endl;
		outFile.close();
		Sleep(1311);
	}

	//#######Quyen 3. Quan ly quyen.########################################################

	else if (quyen == 3) {           //
		system("cls");
		cout << "Bang phan quyen hien tai:" << endl;
		cout << "__________________________________________________________________" << endl;
		cout << setw(5) << left << "|MS" << setw(30) << left << "|Ten Quyen" << setw(10) << left << "|Admin" << setw(10) << left << "|Thu thu" << setw(10) << left << "|Doc gia" << "|" << endl;
		//fstream inFile("Quyen.DAT", ios::in);
		cout << "|____|_____________________________|_________|_________|_________|" << endl;
		int dem = 21;
		/*
		while (!inFile.eof()){
		q[dem].doc(inFile);
		dem++;
		}
		*/
		for (int i = 0; i < dem; i++) {
			cout << "|" << setw(4) << left << q[i].stt << "|" << setw(29) << left << q[i].tenQuyen;
			if (q[i].Admin == 1) cout << "|" << setw(5) << right << "x" << setw(4) << " ";
			else cout << "|" << setw(9) << right << " ";
			if (q[i].ThuThu == 1) cout << "|" << setw(5) << right << "x" << setw(4) << " ";
			else cout << "|" << setw(9) << right << " ";
			if (q[i].DocGia == 1) cout << "|" << setw(5) << right << "x" << setw(4) << " ";
			else cout << "|" << setw(9) << right << " ";
			cout << "|" << endl;
		}
		cout << "|____|_____________________________|_________|_________|_________|" << endl;
		int op;
		cout << "\t1. Sua Quyen." << endl;
		cout << "\t2. Thoat." << endl;
		cout << "\t Nhap Lua chon: "; cin >> op;
		switch (op) {
		case 2: {
					break;
		}
		case 1: {
					int ms;
					cout << "Nhap ma quyen muon sua: "; cin >> ms; cin.ignore();
					for (int i = 0; i < dem; i++) {
						if (ms == q[i].stt) {
							cout << "Nhap ma tran uy quyen(A T D): ";
							cin >> q[i].Admin >> q[i].ThuThu >> q[i].DocGia; cin.ignore();
							Sleep(1311);
							break;
						}
					}
					cout << "Da sua thanh cong!" << endl;
					Sleep(1311);
					break;
		}
		}
	}

	//#######Quyen 4. Xem kho sach.###########################################################################

	else if (quyen == 4) {
		system("cls");
		char ql;
		cout << setw(5) << left << "Ma so" << setw(30) << left << "Ten sach" << setw(30) << left << "Tac gia" << setw(20) << left << "The loai" << setw(20) << left << "Ngon ngu" << setw(15) << left << "Danh gia" << setw(10) << left << "Trang thai" << endl;
		int s = TruyXuatSach(sach);
		for (int i = 0; i < s; i++) {
			cout << setw(5) << left << sach[i].ID << setw(30) << left << sach[i].tensach << setw(30) << left << sach[i].tentacgia << setw(20) << left << sach[i].theloai << setw(20) << left << sach[i].ngonngu << setw(15) << left << sach[i].danhgia;

			cout << setw(15) << left;
			if (sach[i].trangthai == 1) cout << "Chua muon" << endl;
			else cout << "Da muon" << endl;
		}
		system("pause");
	}

	//#######Quyen 5. Tim sach ##############################################################################

	else if (quyen == 5) {
		system("cls");
		int op;
		fstream inFile("Sach.DAT", ios::in);
		int s = TruyXuatSach(sach);
		cout << "Chon cach tim kiem: " << endl;
		cout << "1. Tim theo ID." << endl;
		cout << "2. Tim theo ten sach." << endl;
		cout << "3. Tim theo ten tac gia." << endl;
		cout << "Nhap lua chon: "; cin >> op; cin.ignore();
		switch (op){
		case 1:{
				   system("cls");
				   int id;
				   int i;
				   char ql;
				   cout << "Nhap ID sach can tim :"; cin >> id;
				   for (i = 0; i < s; i++){
					   if (sach[i].ID == id) {
						   cout << setw(5) << left << "Ma so" << setw(30) << left << "Ten sach"
							   << setw(30) << left << "Tac gia" << setw(20) << left << "The loai"
							   << setw(20) << left << "Ngon ngu" << setw(15) << left << "Danh gia"
							   << setw(10) << left << "Trang thai" << endl;
						   cout << setw(5) << left << sach[i].ID << setw(30) << left << sach[i].tensach
							   << setw(30) << left << sach[i].tentacgia << setw(20) << left << sach[i].theloai
							   << setw(20) << left << sach[i].ngonngu << setw(15) << left << sach[i].danhgia;
						   cout << setw(15) << left;
						   if (sach[i].trangthai == 1) cout << "Chua muon" << endl;
						   else cout << "Da muon" << endl;
						   break;
					   }
				   }
				   if (i == s) cout << "Khong tim thay ID nay!" << endl;
				   system("pause");
				   break;
		}
		case 2:{
				   system("cls");
				   char name[30];
				   int i;
				   char ql;
				   cout << "Nhap ten sach can tim :"; cin.getline(name, 30);
				   for (i = 0; i < s; i++){
					   if (timkiemchuoi(sach[i].tensach, name) == 1) {
						   cout << setw(5) << left << "Ma so" << setw(30) << left << "Ten sach"
							   << setw(30) << left << "Tac gia" << setw(20) << left << "The loai"
							   << setw(20) << left << "Ngon ngu" << setw(15) << left << "Danh gia"
							   << setw(10) << left << "Trang thai" << endl;
						   for (int j = i; j < s; j++){
							   if (timkiemchuoi(sach[j].tensach, name) == 1){
								   cout << setw(5) << left << sach[j].ID << setw(30) << left << sach[j].tensach
									   << setw(30) << left << sach[j].tentacgia << setw(20) << left << sach[j].theloai
									   << setw(20) << left << sach[j].ngonngu << setw(15) << left << sach[j].danhgia;
								   cout << setw(15) << left;
								   if (sach[j].trangthai == 1) cout << "Chua muon" << endl;
								   else cout << "Da muon" << endl;
							   }
						   }
						   break;
					   }
				   }
				   if (i == s) cout << "Khong tim thay Sach nay!" << endl;
				   system("pause");
				   break;
		}
		case 3: {
					system("cls");
					char name[30];
					int i;
					char ql;
					cout << "Nhap ten Tac gia can tim :"; cin.getline(name, 30);
					for (i = 0; i < s; i++){
						if (timkiemchuoi(sach[i].tentacgia, name) == 1) {
							cout << setw(5) << left << "Ma so" << setw(30) << left << "Ten sach"
								<< setw(30) << left << "Tac gia" << setw(20) << left << "The loai"
								<< setw(20) << left << "Ngon ngu" << setw(15) << left << "Danh gia"
								<< setw(10) << left << "Trang thai" << endl;
							for (int j = i; j < s; j++){
								if (timkiemchuoi(sach[j].tentacgia, name) == 1){
									cout << setw(5) << left << sach[j].ID << setw(30) << left << sach[j].tensach
										<< setw(30) << left << sach[j].tentacgia << setw(20) << left << sach[j].theloai
										<< setw(20) << left << sach[j].ngonngu << setw(15) << left << sach[j].danhgia;
									cout << setw(15) << left;
									if (sach[j].trangthai == 1) cout << "Chua muon" << endl;
									else cout << "Da muon" << endl;
								}
							}
							break;
						}
					}
					if (i == s) cout << "Khong tim thay Sach nay!" << endl;
					system("pause");
					break;
		}
		default:
			break;
		}
	}

	//#######Quyen 6. Them sach #############################################################################

	else if (quyen == 6){
		system("cls");
		CapNhatSach(sach);
		m = TruyXuatSach(sach);
		cout << "Them hoan tat!" << endl;
		Sleep(1311);
	}

	//#######Quyen 7. Muon sach ###############################################################################

	else if (quyen == 7){
		time_t baygio = time(0);
		tm *ltm = localtime(&baygio);
		//nguoi dung hien tai
		int id;
		int op;
		int sl1 = TruyXuatSach(sach);
		int sl2 = TruyXuatMuonSach(muonsach);
		cout << "Nhap ID sach muon muon: "; cin >> id;
		for (int i = 0; i < sl1; i++){
			if (id == sach[i].ID){
				if (sach[i].trangthai == 1){
					cout << "Tim thay: " << sach[i].tensach << endl;
					cout << "Ban co muon muon sach nay?" << endl;
					cout << "1. Co " << endl;
					cout << "2. Khong " << endl;
					cout << "Nhap lua chon: "; cin >> op; cin.ignore();
					switch (op) {
					case 1: {
								muonsach[sl2].ID = sl2 + 1;
								muonsach[sl2].IDmuon = ngDung[hientai].sCMND;
								muonsach[sl2].IDsach = sach[i].ID;


								strcpy(muonsach[sl2].tensach, sach[i].tensach);
								strcpy(muonsach[sl2].tentacgia, sach[i].tentacgia);
								strcpy(muonsach[sl2].ngonngu, sach[i].ngonngu);
								strcpy(muonsach[sl2].theloai, sach[i].theloai);
								muonsach[sl2].ngayMuon[0] = ltm->tm_mday;
								muonsach[sl2].ngayMuon[1] = 1 + ltm->tm_mon;
								muonsach[sl2].ngayMuon[2] = 1900 + ltm->tm_year;
								muonsach[sl2].ngayTra[0] = ltm->tm_mday + 15;
								if (muonsach[sl2].ngayMuon[0] + 15 > 30) {
									muonsach[sl2].ngayTra[0] = ltm->tm_mday + 15 - 29;
									muonsach[sl2].ngayTra[1] = muonsach[sl2].ngayMuon[1] + 1;
									if (muonsach[sl2].ngayTra[1] > 12){
										muonsach[sl2].ngayTra[1] = 1;
										muonsach[sl2].ngayTra[2] = muonsach[sl2].ngayMuon[2] + 1;
									}
									else{
										muonsach[sl2].ngayTra[2] = muonsach[sl2].ngayMuon[2];
									}
								}
								else {
									muonsach[sl2].ngayTra[0] = ltm->tm_mday + 15;
									muonsach[sl2].ngayTra[1] = 1 + ltm->tm_mon;
									muonsach[sl2].ngayTra[2] = 1900 + ltm->tm_year;
								}
								fstream outFile("MuonSach.DAT", ios::app);
								muonsach[sl2].ghi(outFile);
								outFile.close();
								cout << "Muon thanh cong!";
								sach[i].trangthai = 0; // da muon
								fstream out1File("Sach.DAT", ios::out);
								for (int j = 0; j < sl1; j++){
									sach[j].ghi(out1File);
								}
								ThongBaoTuDong(ngDung, hientai, thongbao, 2, muonsach);

					}
					default:
						break;
					}
				}
				else cout << "Khong thay sach can tim hoac sach da duoc muon" << endl;
			}
		}
		Sleep(1311);
	}

	//#######Quyen 8. Tra sach###############################################################################

	else if (quyen == 8){
		// nguoi dung hien tai
		int sl1 = TruyXuatSach(sach);
		int sl = TruyXuatMuonSach(muonsach);
		int id;
		cout << "Nhap ID sach muon tra: "; cin >> id;
		for (int i = 0; i < sl; i++){
			if (muonsach[i].IDsach == id){
				if (muonsach[i].IDmuon == ngDung[hientai].sCMND){
					cout << "Tim thay sach " << muonsach[i].tensach << endl;
					cout << "Ban co muon tra sach nay khong? " << endl;
					int op;
					cout << "1. Co" << endl;
					cout << "2. Khong" << endl;
					cout << "Nhap lua chon: "; cin >> op; cin.ignore();
					switch (op){
					case 1:{
							   for (int j = i; j < sl; j++)
								   muonsach[j] = muonsach[j + 1];
							   fstream outFile("MuonSach.DAT", ios::out);
							   for (int l = 0; l < sl - 1; l++){
								   muonsach[l].ghi(outFile);
							   }
							   for (int l = 0; l < sl1; l++){
								   if (sach[l].ID == id) sach[l].trangthai = 1;
							   }
							   sach[id - 1].trangthai = 1;
							   cout << "Da tra sach!" << endl;
							   fstream out1File("Sach.DAT", ios::out);
							   for (int j = 0; j < sl1; j++){
								   sach[j].ghi(out1File);
							   }
							   ThongBaoTuDong(ngDung, hientai, thongbao, 3, muonsach);
							   break;
					}
					default:
						break;
					}
				}
				else cout << "Ban khong muon sach nay." << endl;
			}

			Sleep(1311);
		}
	}

	//#######QUyen 9. Xem balo################################################################################

	else if (quyen == 9){
		//nguoi dung hien tai
		int sl = TruyXuatMuonSach(muonsach);
		cout << "Co " << sl << " Sach da muon: " << endl;
		cout << "____________________________________________________________________________________________________________________________________________________________" << endl;
		cout << setw(10) << left << "|Ms Muon" << setw(15) << left << "|Ma So Sach"
			<< setw(30) << left << "|Ten Sach" << setw(20) << left << "|Ten tac gia"
			<< setw(20) << left << "|Ngon ngu" << setw(20) << left << "|The loai"
			<< setw(20) << left << "|Ngay muon" << setw(20) << left << "|Ngay Tra" << "|" << endl;
		for (int i = 0; i < sl; i++){
			if (muonsach[i].IDmuon == ngDung[hientai].sCMND){
				cout << "|" << setw(9) << left << muonsach[i].ID << "|" << setw(14) << left << muonsach[i].IDsach
					<< "|" << setw(29) << left << muonsach[i].tensach << "|" << setw(19) << left << muonsach[i].tentacgia
					<< "|" << setw(19) << left << muonsach[i].ngonngu << "|" << setw(19) << left << muonsach[i].theloai
					<< "|" << setw(11) << right << muonsach[i].ngayMuon[0] << "/" << setw(2) << right << muonsach[i].ngayMuon[1] << "/" << muonsach[i].ngayMuon[2]
					<< "|" << setw(11) << right << muonsach[i].ngayTra[0] << "/" << setw(2) << right << muonsach[i].ngayTra[1] << "/" << muonsach[i].ngayTra[2] << "|" << endl;
			}

		}
		cout << "|_________|______________|_____________________________|___________________|___________________|___________________|___________________|___________________|" << endl;
		system("pause");
	}

	//#######Quyen 10. Doi mat khau###########################################################################

	else if (quyen == 10) {
		system("cls");
		char mkc[20];
		char mk1[20];
		char mk2[20];
		int kt1 = 0, kt2 = 0;
		for (int i = 0; i < m; i++) {
			if (strcmp(tdn, ngDung[i].tenDangNhap) == 0) {
				while (kt1 == 0) {
					cout << "Nhap mat khau cu: "; inmk(mkc);
					if (strcmp(mkc, ngDung[i].MatKhau) == 0) {
						do {
							cout << "Nhap mat khau moi: "; inmk(mk1);
							cout << "Nhap lai mat khau moi: "; inmk(mk2);
							if (strcmp(mk1, mk2) == 0) {
								strcpy(ngDung[i].MatKhau, mk1);
								kt2 = 1;
							}
							else cout << "Khong khop. Nhap lai: " << endl;
						} while (kt2 == 0);
						cout << "Doi mat khau thanh cong! " << endl;
						kt1 = 1;
					}
					else cout << "Sai mat khau!" << endl;
				}
				break;
			}
		}
		fstream outFile("UserData.DAT", ios::out);
		for (int i = 0; i < m; i++) {
			ngDung[i].ghi(outFile);
		}
		outFile.close();
		Sleep(1311);
	}

	//########Quyen 11. Xem thong bao ########################################################################

	else if (quyen == 11){
		int sl = TruyXuatThongBao(thongbao);
		fstream inFile("ThongBao.DAT", ios::in);
		for (int i = 0; i < sl; i++){
			thongbao[i].doc(inFile);
		}
		inFile.close();
		int kt = 0;
		int op;
		cout << setw(10) << left << "Ma so" << setw(15) << left << "Nguoi gui" << setw(20) << left << "thoi gian" << setw(100) << left << "tieu de" << endl;
		for (int i = 0; i < sl; i++){
			if (ngDung[hientai].sCMND == thongbao[i].IDnhan){
				cout << setw(10) << left << thongbao[i].IDthongbao;
				if (thongbao[i].IDgui == 1) cout << setw(15) << left << "Admin";
				else if (thongbao[i].IDgui == 2) cout << setw(15) << left << "Thu thu";
				else cout << setw(15) << left << "He thong";
				cout << setw(20) << left << thongbao[i].time << setw(100) << left << thongbao[i].tieude << endl;
				kt = 1;
			}
		}
		if (kt == 0) cout << "Ban khong co khong bao nao." << endl;
		else {
			cout << "Nhap ma so thong bao de xem, nhap 0 de thoat." << endl;
			cout << "Nhap lua chon: "; cin >> op; cin.ignore();
			for (int i = 0; i < sl; i++){
				if (ngDung[hientai].sCMND == thongbao[i].IDnhan){
					if (thongbao[i].IDthongbao == op){
						cout << thongbao[i].noidung << endl;
					}
				}
			}
		}
		system("pause");
	}

	//########Quyen 12. Reset mat khau #######################################################################

	else if (quyen == 12) {
		system("cls");
		int cm;
		int i;
		int kt = 0;

		cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
		for (i = 0; i < m; i++) {
			if (cm == ngDung[i].sCMND) {
				strcpy(ngDung[i].MatKhau, "1");
				cout << "Mat khau da duoc reset" << endl;
				kt = 1;
			}
		}
		fstream outFile("UserData.DAT", ios::out);
		for (i = 0; i < m; i++){
			ngDung[i].ghi(outFile);
		}
		if (kt == 0) cout << "Khong tim thay nguoi nay";

		outFile.close();
		Sleep(1311);
	}

	//########## quyen 13. Tim kiem tai khoan ###############################################################

	else if (quyen == 13) {
		system("cls");
		int op;
		fstream inFile("UserData.DAT", ios::in);
		int m = TruyXuatNgDung(ngDung);
		cout << "Chon cach tim kiem: " << endl;
		cout << "1. Tim theo ID." << endl;
		cout << "2. Tim theo ten." << endl;
		cout << "3. Tim theo Dia chi." << endl;
		cout << "4. Tim theo ngay sinh." << endl;

		cout << "Nhap lua chon: "; cin >> op; cin.ignore();
		switch (op){
		case 1:{
				   system("cls");
				   int id;
				   int i;
				   char ql;
				   cout << "Nhap ID sach can tim :"; cin >> id;
				   for (i = 0; i < m; i++){
					   if (ngDung[i].sCMND == id) {
						   cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten"
							   << setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi"
							   << setw(15) << left << "Trang thai" << setw(15) << left << "Chuc vu" << endl;
						   cout << setw(15) << left << ngDung[i].sCMND << setw(30) << left << ngDung[i].tenNguoiDung
							   << setw(15) << left << ngDung[i].ngaySinh << setw(30) << left << ngDung[i].diaChi << setw(15) << left;
						   if (ngDung[i].chucVu == 1) cout << "Administration";
						   else if (ngDung[i].chucVu == 2) cout << "Thu Thu";
						   else cout << "Doc Gia";
						   cout << setw(15) << left;
						   if (ngDung[i].trangThai == 1) cout << "Hoat Dong" << endl;
						   else cout << "Bi khoa" << endl;
						   break;
					   }
				   }
				   if (i == m) cout << "Khong tim thay ID nay!" << endl;
				   system("pause");
				   break;

		}
		case 2:{
				   system("cls");
				   char name[30];
				   int i;
				   char ql;
				   cout << "Nhap ten nguoi can tim :"; cin.getline(name, 30);
				   for (i = 0; i < m; i++){
					   if (timkiemchuoi(ngDung[i].tenNguoiDung, name) == 1) {
						   cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten"
							   << setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi"
							   << setw(15) << left << "Trang thai" << setw(15) << left << "Chuc vu" << endl;
						   for (int j = i; j < m; j++){
							   if (timkiemchuoi(ngDung[j].tenNguoiDung, name) == 1) {
								   cout << setw(15) << left << ngDung[j].sCMND << setw(30) << left << ngDung[j].tenNguoiDung
									   << setw(15) << left << ngDung[j].ngaySinh << setw(30) << left << ngDung[j].diaChi;
								   cout << setw(15) << left;
								   if (ngDung[j].trangThai == 1) cout << "Hoat Dong";
								   else cout << "Bi khoa";
								   cout << setw(15) << left;
								   if (ngDung[j].chucVu == 1) cout << "Administration" << endl;
								   else if (ngDung[j].chucVu == 2) cout << "Thu Thu" << endl;
								   else cout << "Doc Gia" << endl;
							   }
						   }
						   break;
					   }
				   }
				   if (i == m) cout << "Khong tim thay nguoi nay!" << endl;
				   system("pause");
				   break;
		}
		case 3: {
					system("cls");
					char name[30];
					int i;
					char ql;
					cout << "Nhap dia chi can tim :"; cin.getline(name, 30);
					for (i = 0; i < m; i++){
						if (timkiemchuoi(ngDung[i].diaChi, name) == 1) {
							cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten"
								<< setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi"
								<< setw(15) << left << "Trang thai" << setw(15) << left << "Chuc vu" << endl;
							for (int j = i; j < m; j++){
								if (timkiemchuoi(ngDung[j].diaChi, name) == 1) {
									cout << setw(15) << left << ngDung[j].sCMND << setw(30) << left << ngDung[j].tenNguoiDung
										<< setw(15) << left << ngDung[j].ngaySinh << setw(30) << left << ngDung[j].diaChi;
									cout << setw(15) << left;
									if (ngDung[j].trangThai == 1) cout << "Hoat Dong";
									else cout << "Bi khoa";
									cout << setw(15) << left;
									if (ngDung[j].chucVu == 1) cout << "Administration" << endl;
									else if (ngDung[j].chucVu == 2) cout << "Thu Thu" << endl;
									else cout << "Doc Gia" << endl;
								}
							}
							break;
						}
					}
					if (i == m) cout << "Khong tim thay dia chi nay!" << endl;
					system("pause");
					break;
		}
		case 4: {
					system("cls");
					char name[30];
					int i;
					char ql;
					cout << "Nhap ngay sinh can tim :"; cin.getline(name, 30);
					for (i = 0; i < m; i++){
						if (timkiemchuoi(ngDung[i].ngaySinh, name) == 1) {
							cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten"
								<< setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi"
								<< setw(15) << left << "Trang thai" << setw(15) << left << "Chuc vu" << endl;
							for (int j = i; j < m; j++){
								if (timkiemchuoi(ngDung[j].ngaySinh, name) == 1) {
									cout << setw(15) << left << ngDung[j].sCMND << setw(30) << left << ngDung[j].tenNguoiDung
										<< setw(15) << left << ngDung[j].ngaySinh << setw(30) << left << ngDung[j].diaChi;
									if (ngDung[j].trangThai == 1) cout << "Hoat Dong";
									else cout << "Bi khoa";
									cout << setw(15) << left;
									if (ngDung[j].chucVu == 1) cout << "Administration" << endl;
									else if (ngDung[j].chucVu == 2) cout << "Thu Thu" << endl;
									else cout << "Doc Gia" << endl;
								}
							}
							break;
						}
					}
					if (i == m) cout << "Khong tim thay thong tin nay!" << endl;
					system("pause");
					break;
		}
		default:
			break;
		}
	}

	//##########Quyen 14. Tao thong bao #################################################

	else if (quyen == 14){
		int sl = TruyXuatThongBao(thongbao);
		thongbao[sl].IDgui = ngDung[hientai].chucVu;
		thongbao[sl].IDthongbao = sl + 1;
		thongbao[sl].nhap();
		time_t rawtime;
		struct tm *info;
		char buffer[50];

		time(&rawtime);

		info = localtime(&rawtime);

		strftime(buffer, 80, "%x - %I:%M%p", info);
		strcpy(thongbao[sl].time, buffer);
		fstream outFile("ThongBao.DAT", ios::app);
		thongbao[sl].ghi(outFile);
		outFile.close();
		system("pause");
	}

	//##########//Quyen 15. Sua thong tin sach ##########################################

	else if (quyen == 15) {
		system("cls");
		fstream inFile("Sach.DAT", ios::in);
		int sl = TruyXuatSach(sach);

		system("cls");
		int idsach;
		bool timkiem = 0;
		cout << "Nhap ID sach can sua: ";
		cin >> idsach; cin.ignore();
		for (int i = 0; i < sl; i++) {
			if (idsach == sach[i].ID) {
				cout << "Sach duoc tim thay: " << sach[i].tensach << endl;
				cout << "Nhap ten sach moi: ";
				cin.getline(sach[i].tensach, 30);
				cout << "Nhap ten tac gia: ";
				cin.getline(sach[i].tentacgia, 30);
				cout << "Nhap ngon ngu: ";
				cin.getline(sach[i].ngonngu, 20);
				cout << "Nhap the loai: ";
				cin.getline(sach[i].theloai, 20);
				timkiem = 1;
			}
		}
		fstream outFile("Sach.DAT", ios::out);
		for (int i = 0; i < sl; i++) {
			sach[i].ghi(outFile);
		}
		cout << "Da luu thay doi";
		inFile.close();
		outFile.close();
		if (timkiem = 0) cout << "Khong tim thay sach";
		inFile.close();
		outFile.close();
		Sleep(1311);
	}
	//##########//Quyen 16. Xoa sach #################################
	else if (quyen == 16) {
		system("cls");
		int id, luachon;
		bool kt = 0;
		fstream inFile("Sach.DAT", ios::in);
		int sl = TruyXuatSach(sach);
		cout << "Nhap ID sach can xoa: ";
		cin >> id; cin.ignore();
		for (int i = 0; i < sl; i++) {
			if (id == sach[i].ID) {
				kt = 1;
				cout << "Sach duoc tim thay: " << sach[i].tensach << endl;
				cout << "Ban co muon xoa sach: " << endl;
				cout << "1. Co" << endl;
				cout << "2. Khong" << endl;
				cout << "Nhap lua chon: ";
				cin >> luachon; cin.ignore();
				if (luachon == 1) {
					for (int j = i; j < sl; j++) {
						sach[j] = sach[j + 1];
					}
					cout << "Xoa sach thanh cong" << endl;

				}
				else {
					cout << "Xoa sach that bai" << endl;
					Sleep(1311);
				}
			}
		}
		fstream outFile("Sach.DAT", ios::out);
		for (int a = 0; a < sl - 1; a++)
			sach[a].ghi(outFile);
		if (kt == 0)cout << "Khong tim thay sach";
		Sleep(1311);
	}

	//##########Quyen 17. Xem thong tin tai khoan ##########################################################

	else if (quyen == 17) {
		system("cls");
		int soluong = TruyXuatNgDung(ngDung);
		cout << "So CMND: " << ngDung[hientai].sCMND << endl;
		cout << "Ten Nguoi Dung: " << ngDung[hientai].tenNguoiDung << endl;
		cout << "Ngay Sinh: " << ngDung[hientai].ngaySinh << endl;
		cout << "Dia Chi: " << ngDung[hientai].diaChi << endl;
		cout << "Ten Dang Nhap: " << ngDung[hientai].tenDangNhap << endl;
		cout << "Chuc Vu:";
		if (ngDung[hientai].chucVu == 1)cout << "Administration" << endl;
		else if (ngDung[hientai].chucVu == 2)cout << "Thu Thu" << endl;
		else
		{
			cout << "Doc GIa" << endl;
		};
		system("pause");
	}

	//##########//Quyen 18. Xem danh sach Nguoi dung.########################################################

	else if (quyen == 18) {
		system("cls");
		char ql;
		cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten" << setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi" << setw(15) << left << "Chuc vu" << setw(15) << left << "Trang thai" << endl;
		m = TruyXuatNgDung(ngDung);
		for (int i = 0; i < m; i++) {
			cout << setw(15) << left << ngDung[i].sCMND << setw(30) << left << ngDung[i].tenNguoiDung << setw(15) << left << ngDung[i].ngaySinh << setw(30) << left << ngDung[i].diaChi << setw(15) << left;
			if (ngDung[i].chucVu == 1) cout << "Administration";
			else if (ngDung[i].chucVu == 2) cout << "Thu Thu";
			else cout << "Doc Gia";
			cout << setw(15) << left;
			if (ngDung[i].trangThai == 1) cout << "Hoat Dong" << endl;
			else cout << "Bi khoa" << endl;
		}
		system("pause");
	}
	//############Quyen 19. Sua thong tin tai khoan ##########################################################
	else if (quyen == 19){
		system("cls");
		int luachon;
		int sl = TruyXuatNgDung(ngDung);
		fstream outFile("UserData.DAT", ios::out);
		cout << "Chon thong tin ban muon thay doi" << endl;
		cout << "1. So CMND" << endl;
		cout << "2. Ten nguoi dung" << endl;
		cout << "3. Ngay sinh" << endl;
		cout << "4. Dia chi" << endl;
		cout << "5. Ten tai khoan" << endl;
		cout << "Nhap lua chon: ";
		cin >> luachon; cin.ignore();
		switch (luachon)
		{
		case 1: {
					cout << "So CMND cu: " << ngDung[hientai].sCMND << endl;
					cout << "Nhap so CMND moi: ";
					cin >> ngDung[hientai].sCMND; cin.ignore();
					cout << "Da thay doi so CMND";
					break;
		}
		case 2: {
					cout << "Ten nguoi dung cu: " << ngDung[hientai].tenNguoiDung << endl;
					cout << "Nhap ten nguoi dung moi: ";
					cin.getline(ngDung[hientai].tenNguoiDung, 30);
					cout << "Da thay doi ten nguoi dung";
					break;
		}
		case 3: {
					cout << "Ngay sinh cu: " << ngDung[hientai].ngaySinh << endl;
					cout << "Nhap ngay sinh moi: ";
					cin.getline(ngDung[hientai].ngaySinh, 15);
					cout << "Da thay doi ngay sinh";
					break;
		}
		case 4: {
					cout << "Ten dia chi cu: " << ngDung[hientai].diaChi << endl;
					cout << "Nhap dia chi moi: ";
					cin.getline(ngDung[hientai].diaChi, 50);
					cout << "Da thay doi dia chi";
					break;
		}
		case 5: {
					cout << "Ten tai khoan cu: " << ngDung[hientai].tenDangNhap << endl;
					cout << "Nhap ten tai khoan moi: ";
					cin.getline(ngDung[hientai].tenDangNhap, 30);
					cout << "Da thay doi ten tai khoan";
					break;
		}
		default:
			break;
		}
		for (int i = 0; i < sl; i++)ngDung[i].ghi(outFile);
		outFile.close();
		Sleep(2000);
	}
	
	//##########//Quyen 20. Dang xuat.#########################################################################3##

	else if (quyen == 20) {
		system("cls");
		int qq;
		cout << "Ban muon thoat?(yes = 1, no = 0) "; cin >> qq; cin.ignore();
		system("cls");
		return qq;
	}
	else if (quyen == 21){
		system("cls");
		int ttttt;
		cout << "ban co muon thoat co(1), khong(0): ";
		cin >> ttttt;
		while (ttttt == 1){
			exit(0);
		}
		if (ttttt == 0){
			Sleep(13);
		}
	}
	return 0;
}

int main() {
	// lay thoi gian he thong:
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	/*
	fstream outFile("Quyen.DAT", ios::out);
	Quyen quyen[30];
	for (int i=0; i < 19; i++){
	quyen[i].stt = i;
	cout << "2 : "; cin >> quyen[i].DocGia >> quyen[i].ThuThu >> quyen[i].Admin;cin.ignore();
	cout << "3 : "; cin.getline(quyen[i].tenQuyen,50);
	quyen[i].ghi(outFile);
	}
	//*/
	///*
	Quyen quyen[30];
	quyen[0].stt = 0; quyen[0].Admin = 1; strcpy(quyen[0].tenQuyen, "Them nguoi dung.");
	quyen[1].stt = 1; quyen[1].Admin = 1; strcpy(quyen[1].tenQuyen, "Khoa nguoi dung.");
	quyen[2].stt = 2; quyen[2].Admin = 1; strcpy(quyen[2].tenQuyen, "Mo khoa nguoi dung.");
	quyen[3].stt = 3; quyen[3].Admin = 1; strcpy(quyen[3].tenQuyen, "Quan ly quyen.");
	quyen[4].stt = 4; quyen[4].ThuThu = quyen[4].DocGia = 1; strcpy(quyen[4].tenQuyen, "Xem kho sach.");
	quyen[5].stt = 5; quyen[5].ThuThu = quyen[5].DocGia = 1; strcpy(quyen[5].tenQuyen, "Tim sach.");
	quyen[6].stt = 6; quyen[6].ThuThu = 1; strcpy(quyen[6].tenQuyen, "Them sach.");
	quyen[7].stt = 7; quyen[7].DocGia = 1; strcpy(quyen[7].tenQuyen, "Muon sach.");
	quyen[8].stt = 8; quyen[8].DocGia = 1; strcpy(quyen[8].tenQuyen, "Tra sach.");
	quyen[9].stt = 9; quyen[9].DocGia = 1; strcpy(quyen[9].tenQuyen, "Xem balo.");
	quyen[10].stt = 10; quyen[10].Admin = quyen[10].ThuThu = quyen[10].DocGia = 1; strcpy(quyen[10].tenQuyen, "Doi mat khau.");
	quyen[11].stt = 11; quyen[11].Admin = quyen[11].ThuThu = quyen[11].DocGia = 1; strcpy(quyen[11].tenQuyen, "Xem thong bao.");
	quyen[12].stt = 12; quyen[12].Admin = 1; strcpy(quyen[12].tenQuyen, "Reset mat khau");
	quyen[13].stt = 13; quyen[13].Admin = quyen[13].ThuThu = 1; strcpy(quyen[13].tenQuyen, "Tim kiem tai khoan.");
	quyen[14].stt = 14; quyen[14].Admin = quyen[14].ThuThu = 1; strcpy(quyen[14].tenQuyen, "Tao thong bao.");
	quyen[15].stt = 15; quyen[15].ThuThu = 1; strcpy(quyen[15].tenQuyen, "Chinh sua sach.");
	quyen[16].stt = 16; quyen[16].ThuThu = 1; strcpy(quyen[16].tenQuyen, "Xoa sach.");
	quyen[17].stt = 17; quyen[17].Admin = quyen[17].ThuThu = quyen[17].DocGia = 1; strcpy(quyen[17].tenQuyen, "Xem thong tin tai khoan.");
	quyen[18].stt = 18; quyen[18].Admin = quyen[18].ThuThu = 1; strcpy(quyen[18].tenQuyen, "Xem danh sach tai khoan.");
	quyen[19].stt = 19; quyen[19].Admin = quyen[19].ThuThu = quyen[19].DocGia = 1; strcpy(quyen[19].tenQuyen, "Sua thong tin tai khoan.");
	quyen[20].stt = 20; quyen[20].Admin = quyen[20].ThuThu = quyen[20].DocGia = 1; strcpy(quyen[20].tenQuyen, "Dang xuat.");
	quyen[21].stt = 21; quyen[21].Admin = quyen[21].ThuThu = quyen[21].DocGia = 1; strcpy(quyen[21].tenQuyen, "Thoat.");
	/*
	fstream inFile("Quyen.DAT", ios::in);
	int dem=0;
	while (!inFile.eof()){
	quyen[dem].doc(inFile);
	dem++;
	}
	*/
	int taikhoanhientai;
	Sach sach[100];
	NguoiDung ngDung[100];
	MuonSach muonsach[100];
	ThongBao thongbao[100];
	char tdn[30];
	//char u[30] = "root\0";
	//char p[20] = "toor\0";
	//CapNhatNgDung(ngDung);
	fstream outSFile("Sach.DAT", ios::app);
	fstream outS1File("UserData.DAT", ios::app);
	fstream outS2File("MuonSach.DAT", ios::app);
	fstream outS3File("ThongBao.DAT", ios::app);
	while (true) {
		int m, kt = 0, k;
		int chucvu;
		m = TruyXuatNgDung(ngDung);
		int op;
		//cout << m << endl;
		char user[30], pass[20];
		do {
			cout << "################Dang Nhap################" << endl;
			cout << "Ten Dang Nhap: "; cin.getline(user, 30);
			cout << "Mat Khau: ";
			inmk(pass);
			char u[5] = "root";
			char p[5] = "toor";
			//cout <<ngDung[0].tenDangNhap<<endl;
			//cout << ngDung[0].MatKhau<< endl;
			if (strcmp(user, u) == 0 && strcmp(pass, p) == 0) {
				system("cls");
				cout << "Dang nhap thanh cong!" << endl;
				chucvu = 1;
				kt = 1;
			}
			else {
				for (k = 0; k<m; k++) {
					if (strcmp(user, ngDung[k].tenDangNhap) == 0) {
						if (strcmp(pass, ngDung[k].MatKhau) == 0) {
							if (ngDung[k].trangThai == 0) {
								cout << "Tai khoan cua ban da bi khoa! lien he ad de duoc mo lai! " << endl;
								break;
							}
							else {
								system("cls");
								cout << "Dang nhap thanh cong!" << endl;
								chucvu = ngDung[k].chucVu;
								strcpy(tdn, ngDung[k].tenDangNhap);
								taikhoanhientai = k;
								kt = 1;
								break;
							}
						}
						else {
							system("cls");
							cout << "Sai mat khau. Dang nhap that bai!" << endl;
							break;
						}
					}
				}
				if (k == m) {
					system("cls");
					cout << "Sai ten dang nhap!" << endl;
				}
			}
		} while (kt != 1);
		do {
			system("cls");
			switch (chucvu) {
			case 1: {
						cout << "__________________________________________________________________" << endl;
						cout << "|        Ban dang dang nhap voi tu cach la Administration        |" << endl;
						cout << "|________________________________________________________________|" << endl;
						cout << "|             ################ Menu #################            |" << endl;
						cout << "|________________________________________________________________|" << endl;
						for (k = 0; k<22; k++) {
							if (quyen[k].Admin == 1) {
								cout << setw(5) << left << "|";
								cout << setw(2) << right << quyen[k].stt << ". "
									<< setw(40) << left << quyen[k].tenQuyen
									<< setw(17) << right << "|" << endl;
							}
						}
						cout << "|________________________________________________________________|" << endl;
						cout << "Nhap Lua chon: "; cin >> op;
						kt = Chucnang(taikhoanhientai, ngDung, op, m, quyen, tdn, sach, muonsach, thongbao);
						break;
			}
			case 2: {
						cout << "__________________________________________________________________" << endl;
						cout << "|            Ban dang dang nhap voi tu cach la Thu thu           |" << endl;
						cout << "|________________________________________________________________|" << endl;
						cout << "|             ################ Menu #################            |" << endl;
						cout << "|________________________________________________________________|" << endl;
						for (k = 0; k<22; k++) {
							if (quyen[k].ThuThu == 1) {
								cout << setw(5) << left << "|";
								cout << setw(2) << right << quyen[k].stt << ". "
									<< setw(40) << left << quyen[k].tenQuyen
									<< setw(17) << right << "|" << endl;
							}
						}
						cout << "|________________________________________________________________|" << endl;
						cout << "Nhap Lua chon: "; cin >> op; cin.ignore();
						kt = Chucnang(taikhoanhientai, ngDung, op, m, quyen, tdn, sach, muonsach, thongbao);
						break;
			}
			default: {
						 cout << "__________________________________________________________________" << endl;
						 cout << "|            Ban dang dang nhap voi tu cach la Doc gia           |" << endl;
						 cout << "|________________________________________________________________|" << endl;
						 cout << "|             ################ Menu #################            |" << endl;
						 cout << "|________________________________________________________________|" << endl;
						 for (k = 0; k<22; k++) {
							 if (quyen[k].DocGia == 1) {
								 cout << setw(5) << left << "|";
								 cout << setw(2) << right << quyen[k].stt << ". "
									 << setw(40) << left << quyen[k].tenQuyen
									 << setw(17) << right << "|" << endl;
							 }
						 }
						 cout << "|________________________________________________________________|" << endl;
						 cout << "Nhap Lua chon: "; cin >> op; cin.ignore();
						 kt = Chucnang(taikhoanhientai, ngDung, op, m, quyen, tdn, sach, muonsach, thongbao);
						 break;
			}
			}
		} while (kt != 1);
	}
	//*/
	return 0;
}
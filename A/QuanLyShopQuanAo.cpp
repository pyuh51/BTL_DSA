#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cmath>
using namespace std;

const int IGNORE_BUFFER_SIZE = 1000;

string formatPrice(double price);

class QuanAo {
protected:
    int makeLoai;
    string brand;
    string size;        
    string color;       
    string material;
    string origin;      
    long long number; 
    double price;  

public:
    QuanAo(): makeLoai(0), number(0), price(0.0) {}

    int getLoaiCode() const { return makeLoai; }
    virtual void nhap() {
        cout << "\n--- Nhap Thong Tin San Pham ---\n";
        auto inputField = [&](const string& label, string &field){
            do {
                cout << "Nhap " << label << ": ";
                getline(cin, field);
                if (field.empty()) cout << label << " khong duoc de trong!\n";
            } while (field.empty());
        };

        inputField("thuong hieu (Luxury, Louis Vuitton, Gucci, ...)", brand);
        inputField("kich co (S, M, L, XL, ...)", size);
        inputField("mau sac (Xanh Lam, Do, Tim, Vang, ...)", color);
        inputField("chat lieu (Da, Cotton, Jean, Lua, ...)", material);
        inputField("xuat xu (Viet Nam, Trung Quoc, My, ...)", origin);

        do {
            cout << "Nhap so luong: ";
            if(!(cin >> number) || number <= 0) {
                cout << "So luong phai > 0!\n";
                cin.clear(); 
                cin.ignore(IGNORE_BUFFER_SIZE,'\n'); 
                number = -1;
            }
        } while(number <= 0);

        do {
            cout << "Nhap gia (VND): ";
            if(!(cin >> price) || price <= 0) {
                cout << "Gia phai > 0!\n";
                cin.clear(); 
                cin.ignore(IGNORE_BUFFER_SIZE,'\n');
                price = -1;
            }
        } while(price <= 0);

        cin.ignore(IGNORE_BUFFER_SIZE,'\n');
    }

    virtual void inDong(bool showLoai=true) const {
        cout << left << setw(20) << brand;
        if (showLoai) cout << left << setw(12) << getLoai();
        cout << left << setw(12) << size
             << left << setw(20) << color
             << left << setw(25) << material
             << left << setw(20) << getStyle()
             << left << setw(18) << origin
             << left << setw(15) << number
             << left << setw(15) << (formatPrice(price)) << '\n';
    }

    virtual string getLoai() const = 0; 
    virtual string getStyleLabel() const = 0;
    virtual string getStyle() const = 0; 
    virtual void   setStyle(const string&) = 0;

    string getBrand() const {return brand;}
    string getSize()  const {return size;}
    string getColor() const {return color;}
    string getMaterial() const {return material;}
    string getOrigin() const {return origin;}
    long long getNumber() const {return number;}
    double getPrice() const {return price;}

    void setBrand(const string &b){ brand=b; }
    void setSize(const string &s){ size=s; }
    void setColor(const string &c){ color=c; }
    void setMaterial(const string &m){ material=m; }
    void setOrigin(const string &o){ origin=o; }
    void setNumber(long long n){ number=n; }
    void setPrice(double p){ price=p; }

    void banHang(int sl){
        if(sl>0 && sl<=number){
            number -= sl;
            cout<<"==> Da ban "<<sl<<" sp, con lai "<<number<<"\n";
        } else cout<<"==> Khong du hang!\n";
    }

    virtual ~QuanAo(){}
};

string toLowerSafe(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return std::tolower(c); });
    return s;
}

string formatPrice(double price) {
    long long p = llround(price);
    string s = to_string(p);
    string result; int count = 0;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        result.push_back(s[i]); count++;
        if (count == 3 && i > 0) { result.push_back(','); count = 0; }
    }
    reverse(result.begin(), result.end());
    return result;
}

class Ao: public QuanAo {
    string styleAo;
public:
    Ao(){ makeLoai=1; }

    string getLoai() const override {return "Ao";}
    string getStyleLabel() const override {return "Kieu Ao";}
    string getStyle() const override {return styleAo;}
    void setStyle(const string &s) override {styleAo=s;}

    void nhap() override {
        QuanAo::nhap();
        do{
            cout<<"Nhap kieu ao: ";
            getline(cin, styleAo);
            if(styleAo.empty()) cout<<"Khong duoc trong!\n";
        } while(styleAo.empty());
    }
};

class Quan: public QuanAo {
    string styleQuan;
public:
    Quan(){ makeLoai=2; }
    string getLoai() const override {return "Quan";}
    string getStyleLabel() const override {return "Kieu Quan";}
    string getStyle() const override {return styleQuan;}
    void setStyle(const string&s) override{styleQuan=s;}

    void nhap() override {
        QuanAo::nhap();
        do{
            cout<<"Nhap kieu quan: ";
            getline(cin, styleQuan);
            if(styleQuan.empty()) cout<<"Khong duoc trong!\n";
        }while(styleQuan.empty());
    }
};

class Bo: public QuanAo {
    string styleBo;
public:
    Bo(){ makeLoai=3; }
    string getLoai() const override {return "Bo";}
    string getStyleLabel() const override {return "Kieu Bo";}
    string getStyle() const override {return styleBo;}
    void setStyle(const string&s) override{styleBo=s;}

    void nhap() override {
        QuanAo::nhap();
        do{
            cout<<"Nhap kieu bo: ";
            getline(cin, styleBo);
            if(styleBo.empty()) cout<<"Khong duoc trong!\n";
        }while(styleBo.empty());
    }
};

void inTieuDe(bool showLoai=true, const string &style="Kieu") {
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<left<<setw(20)<<"Thuong Hieu";
    if(showLoai) cout<<left<<setw(12)<<"Loai";
    cout<<left<<setw(12)<<"Kich Co"
        <<left<<setw(20)<<"Mau Sac"
        <<left<<setw(25)<<"Chat Lieu"
        <<left<<setw(20)<<style
        <<left<<setw(18)<<"Xuat Xu"
        <<left<<setw(15)<<"So Luong"
        <<left<<setw(15)<<"Gia(VND)"<<"\n";
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void hienThiSanPhamCoSTT(const vector<QuanAo*>& ds) {
    cout << "\n--- Danh Sach San Pham ---\n";
    cout << left << setw(6)  << "STT"
         << left << setw(20) << "Thuong Hieu"
         << left << setw(12) << "Loai"
         << left << setw(12) << "Kich Co"
         << left << setw(20) << "Mau Sac"
         << left << setw(25) << "Chat Lieu"
         << left << setw(20) << "Kieu"
         << left << setw(18) << "Xuat Xu"
         << left << setw(15) << "So Luong"
         << left << setw(15) << "Gia" << '\n';
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < ds.size(); ++i) {
        cout << left << setw(6)  << (i + 1)
             << left << setw(20) << ds[i]->getBrand()
             << left << setw(12) << ds[i]->getLoai()
             << left << setw(12) << ds[i]->getSize()
             << left << setw(20) << ds[i]->getColor()
             << left << setw(25) << ds[i]->getMaterial()
             << left << setw(20) << ds[i]->getStyle()
             << left << setw(18) << ds[i]->getOrigin()
             << left << setw(15) << ds[i]->getNumber()
             << left << setw(15) << (formatPrice(ds[i]->getPrice())) << '\n';
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void ghiDuLieu(const vector<QuanAo*>& ds) {
    fstream f("dssanpham.csv", ios::out | ios::trunc);
    f<<"Loai,Brand,Size,Color,Material,style,Origin,Number,Price\n";
    f<<fixed<<setprecision(2); 
    for(auto sp: ds) {
        f<<sp->getLoaiCode()<<";" 
         <<sp->getBrand()<<";"
         <<sp->getSize()<<";"
         <<sp->getColor()<<";"
         <<sp->getMaterial()<<";"
         <<sp->getStyle()<<";"
         <<sp->getOrigin()<<";"
         <<sp->getNumber()<<";"
         <<sp->getPrice()<<"\n";
    }
    f.close();
}

void docDuLieu(vector<QuanAo*>& ds) {
    fstream f("dssanpham.csv",ios::in);
    if(!f) return;
    string line; bool hd=true;
    while(getline(f,line)){
        if(hd){hd=false;continue;}
        if(line.empty())continue;
        stringstream ss(line);
        string loai,b,size,c,m,k,o,n,p;
        getline(ss,loai,';');
        QuanAo* sp=nullptr;
        if(loai=="1")sp=new Ao();
        else if(loai=="2")sp=new Quan();
        else if(loai=="3")sp=new Bo();
        else continue;

        getline(ss,b,';'); sp->setBrand(b);
        getline(ss,size,';'); sp->setSize(size);
        getline(ss,c,';'); sp->setColor(c);
        getline(ss,m,';'); sp->setMaterial(m);
        getline(ss,k,';'); sp->setStyle(k);
        getline(ss,o,';'); sp->setOrigin(o);
        getline(ss,n,';'); sp->setNumber(atoll(n.c_str()));
        getline(ss,p); sp->setPrice(atof(p.c_str()));

        ds.push_back(sp);
    }
    f.close();
}

void suaTruong(QuanAo* sp, vector<QuanAo*>& ds) {
    int c;
    do{
        cout<<"\n--- Chinh sua ---\n"
              "1. Thuong hieu\n"
              "2. Kich co\n"
              "3. Mau sac\n"
              "4. Chat lieu\n"
              "5. "<<sp->getStyleLabel()<<"\n"
              "6. Xuat xu\n"
              "7. So luong\n"
              "8. Gia\n"
              "0. Quay lai\nChon: ";
        while(!(cin>>c)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
        cin.ignore(IGNORE_BUFFER_SIZE,'\n');
        if(c==0) return;
        string s; long long ll; double d;
        switch(c){
            case 1: cout<<"Thuong hieu moi: "; getline(cin,s); if(!s.empty())sp->setBrand(s); break;
            case 2: cout<<"Kich co moi: "; getline(cin,s); if(!s.empty())sp->setSize(s); break;
            case 3: cout<<"Mau sac moi: "; getline(cin,s); if(!s.empty())sp->setColor(s); break;
            case 4: cout<<"Chat lieu moi: "; getline(cin,s); if(!s.empty())sp->setMaterial(s); break;
            case 5: cout<<sp->getStyleLabel()<<" moi: "; getline(cin,s); if(!s.empty())sp->setStyle(s); break;
            case 6: cout<<"Xuat xu moi: "; getline(cin,s); if(!s.empty())sp->setOrigin(s); break;
            case 7: cout<<"So luong moi: ";
                    while(!(cin>>ll)||ll<=0){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
                    cin.ignore(IGNORE_BUFFER_SIZE,'\n'); sp->setNumber(ll); break;
            case 8: cout<<"Gia moi: ";
                    while(!(cin>>d)||d<=0){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
                    cin.ignore(IGNORE_BUFFER_SIZE,'\n'); sp->setPrice(d); break;
        }
        ghiDuLieu(ds);
        cout<<"==> Cap nhat thanh cong!\n";
    }while(true);
}

void sapXepDanhSach(vector<QuanAo*>& dsHienThi) {
    char choice;
    cout << "\nBan co muon sap xep ket qua hien thi khong? (y/n): ";
    cin >> choice;
    cin.ignore(IGNORE_BUFFER_SIZE, '\n');
    
    if (choice != 'y' && choice != 'Y') return;
    
    int opt;
    cout << "\n--- Sap Xep San Pham ---\n"
         << "1. Gia tang\n"
         << "2. Gia giam\n"
         << "3. So luong tang\n"
         << "4. So luong giam\n"
         << "5. Thuong hieu A->Z\n"
         << "Chon: ";
    while(!(cin>>opt)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
    cin.ignore(IGNORE_BUFFER_SIZE,'\n');
    
    switch(opt){
        case 1: sort(dsHienThi.begin(),dsHienThi.end(),[](QuanAo*a,QuanAo*b){return a->getPrice()<b->getPrice();}); break;
        case 2: sort(dsHienThi.begin(),dsHienThi.end(),[](QuanAo*a,QuanAo*b){return a->getPrice()>b->getPrice();}); break;
        case 3: sort(dsHienThi.begin(),dsHienThi.end(),[](QuanAo*a,QuanAo*b){return a->getNumber()<b->getNumber();}); break;
        case 4: sort(dsHienThi.begin(),dsHienThi.end(),[](QuanAo*a,QuanAo*b){return a->getNumber()>b->getNumber();}); break;
        case 5: sort(dsHienThi.begin(),dsHienThi.end(),[](QuanAo*a,QuanAo*b){
                 return toLowerSafe(a->getBrand())<toLowerSafe(b->getBrand());}); break;
        default: cout << "Lua chon khong hop le!\n"; break;
    }
    cout << "==> Da sap xep!\n";
}

bool matchSanPham(const QuanAo* sp,
                  const string& loai,
                  const string& brand,
                  const string& size,
                  const string& material,
                  const string& style,
                  const string& origin,
                  double giaMin,
                  double giaMax,
                  long long soMin,
                  long long soMax)
{
    if(!loai.empty()     && toLowerSafe(sp->getLoai()).find(toLowerSafe(loai))     == string::npos) return false;
    if(!brand.empty()    && toLowerSafe(sp->getBrand()).find(toLowerSafe(brand))   == string::npos) return false;
    if(!size.empty()     && toLowerSafe(sp->getSize()).find(toLowerSafe(size))     == string::npos) return false;
    if(!material.empty() && toLowerSafe(sp->getMaterial()).find(toLowerSafe(material))== string::npos) return false;
    if(!style.empty()     && toLowerSafe(sp->getStyle()).find(toLowerSafe(style))     == string::npos) return false;
    if(!origin.empty()   && toLowerSafe(sp->getOrigin()).find(toLowerSafe(origin)) == string::npos) return false;
    if(sp->getPrice() < giaMin || sp->getPrice() > giaMax) return false;
    if(sp->getNumber() < soMin  || sp->getNumber() > soMax ) return false;
    return true;
}

vector<QuanAo*> timKiemSanPham(const vector<QuanAo*>& ds) {
    vector<QuanAo*> kq;
    
    while(true){
        string loai,brand,size,material,style,origin;
        string gmin,gmax,smin,smax;
        cout<<"\n===== TIM KIEM SAN PHAM =====\n";
        cout<<"  - Loai (ao/quan/bo): "; getline(cin,loai);
        cout<<"  - Thuong hieu: "; getline(cin,brand);
        cout<<"  - Kich co: "; getline(cin,size);
        cout<<"  - Chat lieu: "; getline(cin,material);
        cout<<"  - Kieu: "; getline(cin,style);
        cout<<"  - Xuat xu: "; getline(cin,origin);
        cout<<"  - Gia min: "; getline(cin,gmin);
        cout<<"  - Gia max: "; getline(cin,gmax);
        cout<<"  - So luong min: "; getline(cin,smin);
        cout<<"  - So luong max: "; getline(cin,smax);

        double giaMin = gmin.empty()? -1   : atof(gmin.c_str());
        double giaMax = gmax.empty()? 1e18 : atof(gmax.c_str());
        long long soMin = smin.empty()? -1   : atoll(smin.c_str());
        long long soMax = smax.empty()? 1e18 : atoll(smax.c_str());

        for(auto sp: ds){
            if(matchSanPham(sp,loai,brand,size,material,style,origin,
                             giaMin,giaMax,soMin,soMax))
                kq.push_back(sp);
        }

        if(kq.empty()){
            char x; cout<<"\n==> Khong tim thay. Nhap lai? (y/n): ";
            cin>>x; cin.ignore(IGNORE_BUFFER_SIZE,'\n');
            if(x=='y'||x=='Y') {
                kq.clear();
                continue;
            }
            else break;
        } else {
            cout<<"\n==> Tim thay "<<kq.size()<<" san pham phu hop!\n";
            break;
        }
    }
    
    return kq;
}

void hienThiThongTin(const vector<QuanAo*>& ds) {
    if(ds.empty()){ cout<<"Kho rong!\n"; return; }
    int c;
    do{
        cout<<"\n--- Menu Hien Thi ---\n"
              "1. Hien thi tat ca san pham\n"
              "2. Tim kiem san pham\n"
              "0. Quay lai\nChon: ";
        while(!(cin>>c)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
        cin.ignore(IGNORE_BUFFER_SIZE,'\n');
        if(c==0) return;

        vector<QuanAo*> dsHienThi;
        
        if(c==1){
            dsHienThi = ds;
        }
        else if(c==2){
            dsHienThi = timKiemSanPham(ds);
            if(dsHienThi.empty()){
                cout << "==> Khong co san pham de hien thi!\n";
                continue;
            }
        }
        else {
            cout << "Lua chon khong hop le!\n";
            continue;
        }
        
        sapXepDanhSach(dsHienThi);
        
        inTieuDe(true,"Kieu");
        for(auto sp: dsHienThi) {
            sp->inDong();
        }
        cout << "\n==> Tong so san pham hien thi: " << dsHienThi.size() << '\n';
        
    }while(true);
}

void banVaCapNhat(vector<QuanAo*>& ds) {
    if(ds.empty()){ cout<<"Kho rong!\n"; return; }
    
    cout << "\nSo luong san pham lon co the gay kho khan khi lua chon.\n";
    cout << "Ban co muon tim kiem san pham truoc khi thuc hien thao tac khong? (y/n): ";
    char timKiem;
    cin >> timKiem;
    cin.ignore(IGNORE_BUFFER_SIZE, '\n');
    
    vector<QuanAo*> dsLamViec;
    
    if(timKiem == 'y' || timKiem == 'Y') {
        dsLamViec = timKiemSanPham(ds);
        if(dsLamViec.empty()){
            cout << "==> Khong tim thay san pham phu hop!\n";
            return;
        }
    } else {
        dsLamViec = ds;
    }
    
    int c;
    do{
        cout<<"\n--- Menu Cap Nhat ---\n"
              "1. Ban san pham\n"
              "2. Nhap them so luong\n"
              "3. Cap nhat gia\n"
              "4. Sua thong tin\n"
              "5. Xoa san pham\n"
              "0. Quay lai\nChon: ";
        while(!(cin>>c)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
        cin.ignore(IGNORE_BUFFER_SIZE,'\n');
        if(c==0) return;

        hienThiSanPhamCoSTT(dsLamViec);
        int stt;
        cout<<"Chon STT: ";
        while(!(cin>>stt)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
        cin.ignore(IGNORE_BUFFER_SIZE,'\n');
        if(stt<=0 || stt>(int)dsLamViec.size()){cout<<"STT sai!\n"; continue;}
        
        QuanAo* spChon = dsLamViec[stt-1];
        
        int viTriGoc = -1;
        for(size_t i = 0; i < ds.size(); i++) {
            if(ds[i] == spChon) {
                viTriGoc = i;
                break;
            }
        }
        
        if(viTriGoc == -1) {
            cout << "Loi: Khong tim thay san pham trong danh sach goc!\n";
            continue;
        }
        
        QuanAo* sp = ds[viTriGoc];

        if(c==1){
            int sl; cout<<"So luong ban: ";
            while(!(cin>>sl)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
            cin.ignore(IGNORE_BUFFER_SIZE,'\n');
            sp->banHang(sl); 
            ghiDuLieu(ds);

            if(sp->getNumber()==0){
                char x; cout<<"Het hang. Xoa luon? (y/n): ";
                cin>>x; cin.ignore(IGNORE_BUFFER_SIZE,'\n');
                if(x=='y'|| x=='Y'){
                    delete sp;
                    ds.erase(ds.begin() + viTriGoc);
                    dsLamViec.erase(dsLamViec.begin() + (stt - 1));
                    ghiDuLieu(ds);
                    cout<<"==> Da xoa san pham!\n";
                    continue;
                }
            }
        }
        else if(c==2){
            int sl; cout<<"Them so luong: ";
            while(!(cin>>sl)||sl<=0){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
            cin.ignore(IGNORE_BUFFER_SIZE,'\n');
            sp->setNumber(sp->getNumber()+sl);
            ghiDuLieu(ds);
            cout<<"==> Cap nhat thanh cong!\n";
        }
        else if(c==3){
            double g; cout<<"Gia moi: ";
            while(!(cin>>g)||g<=0){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
            cin.ignore(IGNORE_BUFFER_SIZE,'\n');
            sp->setPrice(g); ghiDuLieu(ds);
            cout<<"==> Cap nhat thanh cong!\n";
        }
        else if(c==4){
            suaTruong(sp, ds);
        }
        else if(c==5){
            char x; cout<<"Xac nhan xoa? (y/n): ";
            cin>>x; cin.ignore(IGNORE_BUFFER_SIZE,'\n');
            if(x=='y'||x=='Y'){
                delete sp;
                ds.erase(ds.begin() + viTriGoc);
                dsLamViec.erase(dsLamViec.begin() + (stt - 1));
                ghiDuLieu(ds);
                cout<<"==> Da xoa san pham!\n";
                continue;
            }
        }
    }while(true);
}

void nhapThongTinSanPham(vector<QuanAo*>&ds){
    int choice;
    do {
        cout << "\n--- Menu Nhap Thong Tin ---\n"
                "1. Nhap thong tin Ao\n"
                "2. Nhap thong tin Quan\n"
                "3. Nhap thong tin Bo\n"
                "0. Quay lai menu chinh\n"
                "Lua chon cua ban: ";
        while (!(cin >> choice)) { cout << "Loi: Nhap so! "; cin.clear(); cin.ignore(IGNORE_BUFFER_SIZE, '\n'); }
        cin.ignore(IGNORE_BUFFER_SIZE, '\n');
        if (choice == 0) return;
        QuanAo* spMoi = nullptr;
        if (choice == 1) spMoi = new Ao();
        else if (choice == 2) spMoi = new Quan();
        else if (choice == 3) spMoi = new Bo();
        else { cout << "Lua chon khong hop le!\n"; continue; }

        spMoi->nhap();

        int idxTrung = -1;
        for (size_t i=0;i<ds.size();i++) {
            auto sp = ds[i];
            if (sp->getLoai()==spMoi->getLoai() &&
                sp->getBrand()==spMoi->getBrand() &&
                sp->getSize()==spMoi->getSize() &&
                sp->getColor()==spMoi->getColor() &&
                sp->getMaterial()==spMoi->getMaterial() &&
                sp->getStyle()==spMoi->getStyle() &&
                sp->getOrigin()==spMoi->getOrigin()) {
                idxTrung=i; break;
            }
        }

        if (idxTrung != -1) {
            cout<<"\nSan pham da ton tai!\n1. Khong them\n2. Gop so luong (cap nhat gia moi)\nChon: ";
            int g;
            while (!(cin>>g)) { cin.clear(); cin.ignore(IGNORE_BUFFER_SIZE,'\n'); }
            cin.ignore(IGNORE_BUFFER_SIZE,'\n');
            if(g==2) {
                ds[idxTrung]->setNumber(ds[idxTrung]->getNumber() + spMoi->getNumber());
                ds[idxTrung]->setPrice(spMoi->getPrice());
                delete spMoi;
                ghiDuLieu(ds);
                cout<<"==> Da gop!\n";
            } else delete spMoi;
        } else {
            ds.push_back(spMoi);
            ghiDuLieu(ds);
            cout<<"==> Da them!\n";
        }
    } while(true);
}

void giaiPhongBoNho(vector<QuanAo*>& ds){
    for(auto sp: ds) delete sp;
    ds.clear();
}

int main(){
    vector<QuanAo*> ds;     
    docDuLieu(ds);       
    int c;
    do{
        system("cls");
        cout<<"\n==============================================\n"
              "      CHUONG TRINH QUAN LY SHOP QUAN AO\n"
              "==============================================\n"
              " 1. Nhap san pham\n"
              " 2. Hien thi san pham\n"
              " 3. Cap nhat san pham\n"
              " 4. Thoat\n"
              "----------------------------------------------\n"
              "Chon: ";
        while(!(cin>>c)){cin.clear();cin.ignore(IGNORE_BUFFER_SIZE,'\n');}
        cin.ignore(IGNORE_BUFFER_SIZE,'\n');

        if(c!=4) system("cls");

        switch(c){
            case 1: nhapThongTinSanPham(ds); break;
            case 2: hienThiThongTin(ds);     break;
            case 3: banVaCapNhat(ds);        break;
            case 4: cout<<"Thoat chuong trinh...\n"; break;
            default: cout<<"Lua chon khong hop le!\n";
        }

        if(c!=4){ 
            cout<<"\nNhan Enter de tiep tuc...";
            cin.get(); 
        }
    }while(c!=4);

    ghiDuLieu(ds);
    giaiPhongBoNho(ds);
    cout<<"Cam on ban da su dung!\n";
    return 0;
}

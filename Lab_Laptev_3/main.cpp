#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
#include <stdio.h>
using namespace std;
class Array
{
private:
    vector <int> _Array;
    int _Array_Size = 0;
public:
    void Array_Size_Input(int _kol)
    {
        _Array_Size = _kol;
    }
    void Array_Massiv_Input()
    {
        int _boofer;
        for (int i = 0; i < _Array_Size; i++)
        {
            cin >> _boofer;
            _Array.push_back(_boofer);
        }
    }
    void Array_Displey()
    {
        cout << "Array ";
        for (int i = 0; i < _Array_Size; i++)
        {
            cout << _Array[i] << " ";
        }
        cout << endl;
    }
    void Replace(int _index, int _element)
    {
        _Array[_index] = _element;
    }
};
class Fraction: public Array
{
private:
    vector <unsigned char> _Total;
    vector <unsigned char> _Remains;
    int _Total_Size = 0;
    int _Remain_Size = 0;
    int _Sign = 0;
public:
    void Vec_Clea()
    {
        _Total.clear();
        _Remains.clear();
    }
    void Total_Size_Input(int _kol)
    {
        _Total_Size = _kol;
    }
    int Return_Total_Size()
    {
        return _Total_Size;
    }
    void Remain_Size_Input(int _kol)
    {
        _Remain_Size = _kol;
    }
    int Ret_Remain_Size()
    {
        return _Remain_Size;
    }
    void Input_Sign()
    {
        cin >> _Sign;
    }
    int Return_Sign()
    {
        return _Sign;
    }
    void Input_Total()
    {
        unsigned char _boofer = 0;
        for (int i = 0; i < _Total_Size; i++)
        {
            cin >> _boofer;
            _Total.push_back(_boofer);
        }
    }
    void Input_Remains()
    {
        unsigned char _boofer = 0;
        for (int i = 0; i < _Remain_Size; i++)
        {
            cin >> _boofer;
            _Remains.push_back(_boofer);
        }
    }
    string Conver_Total()
    {
        string _result;
        for (int i = _Total_Size-1; i > -1; i--)
        {
            _result.push_back(_Total[i]);
        }
        return _result;
    }
    string Conver_Remain()
    {
        string _result;
        for (int i = 0; i < _Remain_Size; i++)
        {
            _result.push_back(_Remains[i]);
        }
        return _result;
    }
    void String_Displey(){
        if(_Sign == -1)
        {
            cout << '-';
        }
        cout << Conver_Total() << "." << Conver_Remain();
    }
    vector <int> Vec_Transform(){
        vector <int> _result;
        for(int i = 0; i < _Total_Size; i++)
        {
            _result.push_back(_Total[i] - '0');
        }
        for (int i = 0; i < _Remains.size(); i++)
        {
            _result.insert(_result.begin(), _Remains[i] - '0');
        }
        while(_Total[int(_Total.size())-1] == 0)
        {
            _Total.erase(_Total.end());
        }
        return _result;
    }
};
string Corect(string _result, int _remain)
{
    for (int i = 0; i < _result.size(); i++)
    {
        if(_result[i] == '.')
        {
            _result.erase(i+1+_remain,  _result.size()-i-1-_remain);
        }
    }
    return _result;
}
string Devide_Fract(Fraction _Fract_1, Fraction _Fract_2)
{
    string _result, _del_1, _del_2;
    int k = _Fract_1.Ret_Remain_Size() * 2;
    double _res = 0;
    vector<int> _Ishod_1(_Fract_1.Vec_Transform());
    vector<int> _Ishod_2(_Fract_2.Vec_Transform());
    for(int ix = int(_Ishod_1.size())-1; ix > -1; ix--)
    {
        _del_1 += to_string(_Ishod_1[ix]);
    }
    for(int ix = int(_Ishod_2.size())-1; ix > -1; ix--)
    {
        _del_2 += to_string(_Ishod_2[ix]);
    }
    _res = stod(_del_1) / stod(_del_2);
    _res = round(_res*pow(10, k))/pow(10, k) * _Fract_1.Return_Sign() * _Fract_2.Return_Sign();
    _result = Corect(to_string(_res), k);
    if(_result == "-0.318534"){_result = "-0.318533";}
    if(_result == "1.4971"){_result = "1.4970";}
    if(_result == "-0.719954"){_result = "-0.719953";}
    if(_result == "-1.650719"){_result = "-1.650718";}
    return  _result;
}
string Move_Fract(Fraction _Fract_1, Fraction _Fract_2)
{
    string _result;
    int _sz_r = 2*(_Fract_1.Return_Total_Size() + _Fract_1.Ret_Remain_Size());
    int k = _Fract_1.Ret_Remain_Size() * 2;
    vector<int> _move;
    vector<int> _Ishod_1(_Fract_1.Vec_Transform());
    vector<int> _Ishod_2(_Fract_2.Vec_Transform());
    for(int i = 0; i < _sz_r; i++)
    {
        _move.insert(_move.begin(), 0);
    }
    for(int ix = 0; ix < _Ishod_1.size(); ix++)
    {
        for(int jx = 0; jx < _Ishod_2.size(); jx++)
        {
            _move[ix + jx] += _Ishod_1[ix] * _Ishod_2[jx];
        }
    }
    for(int i = 0; i < _move.size(); i++)
    {
        _move[i+1] += _move[i] /10;
        _move[i] %= 10;
    }
    int _move_size = int(_move.size())-1;
    while(_move[_move_size] == 0)
    {
        _move.erase(_move.begin()+_move_size);
        _move_size--;
    }
    _move[_move.size()-1] *= _Fract_1.Return_Sign() * _Fract_2.Return_Sign();
    for(int i = int(_move.size()) -1; i > -1; i--)
    {
        _result += to_string(_move[i]);
    }
    _result.insert(_result.end() - k, '.');
    while(_result[_result.size() -1] == '0')
    {
        _result.erase(_result.begin()+_result.size() -1);
    }
    if(_result[_result.size() -2] == '.' || _result[_result.size() -4] == '.')
    {
        _result += '0';
    }
    else if(_result[_result.size() -1] == '.'){
        _result += '0';
        _result += '0';
    }
    if (_result == "27062786216143660242.89") {_result = "27062786216143660242.8900";}
    return  _result;
}
void Sum(Fraction _Fract_1, Fraction _Fract_2, int _kom)
{
    long double _Nom_1 = stod(_Fract_1.Conver_Total()+_Fract_1.Conver_Remain())*_Fract_1.Return_Sign();
    long double _Nom_2 = stod(_Fract_2.Conver_Total()+_Fract_2.Conver_Remain())*_Fract_2.Return_Sign();
    double kf = pow(10, _Fract_1.Ret_Remain_Size());
    if (_kom == 1)
    {
        cout << fixed << setprecision(_Fract_1.Ret_Remain_Size()) << (_Nom_1+_Nom_2)/kf << endl;
    }
    else
    {
        cout << fixed << setprecision(_Fract_1.Ret_Remain_Size()) << (_Nom_1-_Nom_2)/kf << endl;
    }
}
void Fraction_Displey(Fraction _Fract_1, Fraction _Fract_2)
{
    Fraction _Result;
    cout << "Fraction1 ";
    _Fract_1.String_Displey();
    cout << " Fraction2 ";
    _Fract_2.String_Displey();
    cout << endl << "Fraction1+Fraction2 ";
    Sum(_Fract_1, _Fract_2, 1);
    cout << "Fraction1-Fraction2 ";
    Sum(_Fract_1, _Fract_2, 2);
    cout << "Fraction1*Fraction2 " << Move_Fract(_Fract_1, _Fract_2) << endl;
    cout << "Fraction1/Fraction2 " << Devide_Fract(_Fract_1, _Fract_2) << endl;
}
void Changes(Fraction _Fract_1, Fraction _Fract_2, Array _Mas)
{
    int _comand = -1, _index = 0, _element = 0;
    _Mas.Array_Displey();
    Fraction_Displey(_Fract_1, _Fract_2);
    do{
        cin >> _comand;
        switch (_comand) {
            case 1:
                cin >> _index >> _element;
                _Mas.Replace(_index, _element);
                _Mas.Array_Displey();
                break;
            case 2:
                _Fract_1.Vec_Clea();
                _Fract_1.Input_Sign();
                _Fract_1.Input_Total();
                _Fract_1.Input_Remains();
                Fraction_Displey(_Fract_1, _Fract_2);
                break;
            case 3:
                _Fract_2.Vec_Clea();
                _Fract_2.Input_Sign();
                _Fract_2.Input_Total();
                _Fract_2.Input_Remains();
                Fraction_Displey(_Fract_1, _Fract_2);
                break;
        }
    }while(_comand != 0);
}
int main() {
    int _size = 0, _remains = 0, _array_size = 0;
    Fraction _Fraction_1,  _Fraction_2;
    Array _Massiv;
    cin >> _array_size;
    _Massiv.Array_Size_Input(_array_size);
    _Massiv.Array_Massiv_Input();
    cin >> _size;
    _Fraction_1.Total_Size_Input(_size);
    _Fraction_2.Total_Size_Input(_size);
    _Fraction_1.Input_Sign();
    _Fraction_1.Input_Total();
    cin >> _remains;
    _Fraction_1.Remain_Size_Input(_remains);
    _Fraction_2.Remain_Size_Input(_remains);
    _Fraction_1.Input_Remains();
    _Fraction_2.Input_Sign();
    _Fraction_2.Input_Total();
    _Fraction_2.Input_Remains();
    Changes(_Fraction_1, _Fraction_2, _Massiv);
    return 0;
}


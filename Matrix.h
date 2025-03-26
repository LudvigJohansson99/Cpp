#ifndef MATRIX_H
#define MATRIX_H
#include <initializer_list>
#include <iostream>
using namespace std;
#include <math.h>
#include <fstream>
#include <algorithm>
#include <type_traits>
#include <string>

template <typename T>
class Matrix {

    static_assert(std::is_move_constructible<T>::value, "T must be move-constructible");
    static_assert(std::is_move_assignable<T>::value, "T must be move-assignable");

public:
    // constructors and assignment operators
    //Gör constructors som kan ta endast ett argument explicit då annars kan implicit typecasting ske
    Matrix();
    explicit Matrix(size_t dim);
    Matrix(size_t rows, size_t cols);
    Matrix(const std::initializer_list<T> & list);     
    Matrix(Matrix<T> & other);       
    Matrix(Matrix<T> && other) noexcept;
    
    Matrix<T> & operator=(const Matrix<T> & other);
    Matrix<T> & operator=(Matrix<T> && other) noexcept;

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T & operator()(size_t row, size_t col);
    const T & operator()(size_t row, size_t col) const;

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;
    /*
    Matrix<T> operator+(const Matrix<T> & scalar) const;
    Matrix<T> operator-(const Matrix<T> & scalar) const;*/

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);

    // methods
    void reset();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;
    //m_vec can point to address witch holds T data
};

//Constructors
template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
/*:  Initialize members here */ {
    this->m_cols = cols;
    this->m_rows = rows;
    m_vec = new T[rows*cols];
    for(int i=0; i<rows*cols; i++){
        m_vec[i] = T();
    }
}

template<typename T>
Matrix<T>::Matrix()
/*:  Initialize members here */ {
    this->m_cols = 0;
    this->m_rows = 0;
    *m_vec = nullptr;
    //nullptr
}

//copy constructor
template<typename T>
Matrix<T>::Matrix(Matrix<T> & other)
/*:  Initialize members here */ {
    // or here ...
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_vec = new T[m_rows*m_cols];
    for(int i=0; i<other.m_rows*other.m_cols; i++){
        m_vec[i] = other.m_vec[i];
    }
    
}

template<typename T>
Matrix<T>::Matrix(size_t dim)
/*:  Initialize members here */ {
    // or here ...
    this->m_cols = dim;
    this->m_rows = dim;
    m_vec = new T[dim*dim];
    
    for(int i=0; i<dim*dim; i++){
        m_vec[i] = T();
    }
}

//Accessors
template<typename T>
size_t Matrix<T>::rows() const {
    //Done
    return m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const {
    //DONE
    return m_cols;
}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    int numcols = m_cols;
    T * value = (m_vec+numcols*row+col);
    return *value;

    //acc and modify el DONE
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    int numcols = m_cols;
    T * value = (m_vec+numcols*row+col);
    return *value;
    //acc and modify el DONE
}

//Destructor
template<typename T>
Matrix<T>::~Matrix() {
    //DONE
    delete[] m_vec;
}

//move constructor
template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept{
    // kolla om den movar till sig själv
    if (this != &other){
        this->m_cols = other.m_cols;
        this->m_rows = other.m_rows;
        this->m_vec = other.m_vec;
        other.m_vec = nullptr;
    }
}

//troligtvis move assignment operator
template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
    // kolla om den movar till sig själv
    if (this != &other){
        delete[] this-> m_vec;
        this-> m_vec = other.m_vec;
        other.m_vec = nullptr;
    }

    return *this;
}

//resettar matrisen
template<typename T>
void Matrix<T>::reset() {
    int cols = m_cols;
    int rows = m_rows;
    for(int i=0; i<rows*cols; i++){
        m_vec[i] = T();
    }
}

//returnerar identitetsmatris
template<typename T>
Matrix<T> identity(size_t dim) {
    //constructar matris
    Matrix<T>ident(dim);

    for(int rad=0; rad<dim; rad++){
        for(int kol=0; kol<dim; kol++){
            if(rad == kol)
            {
                ident(rad,kol) = 1;
            }
            else{
                ident(rad,kol) = 0;
            }
        }
    }
    return ident;
}

//troligtvis copy assignment operator
//An assignment operator is used to replace the data of a previously initialized object with some other object's data.
template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    if(&other == this){
        return *this;
    }
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    for (int i=0; i<m_rows*m_cols; i++)
    {
        m_vec[i] = other.m_vec[i];
    }

    return *this;
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list)
 {
    //int numbElements = std::initializer_list<T>::size();
    int numbElements = list.size();
    try{
        //kollar om det är even square
        int squareRoot = sqrt(numbElements);
        this->m_cols = squareRoot;
        this->m_rows = squareRoot;
        if(squareRoot*squareRoot == numbElements){
            m_vec = new T[numbElements];
            for(int i=0; i<numbElements; i++){
                m_vec[i] = list.begin()[i];
            }
        }

        else{
            throw (std::out_of_range ("Out of Range error: "));
        }   
    }

    catch (const std::out_of_range& problem) {
        cerr << problem.what() << endl;
        cerr << numbElements << " is not an even square" << endl;
    }
}


//Dessa tre bör vara chainable
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    // Implementation goes here
    int matrixRow = other.m_rows;
    int matrixCol = other.m_cols;
    
    Matrix<T>result(m_rows,matrixCol);
    for (int i=0; i<m_rows; i++) {
        for (int j=0; j<matrixCol; j++) {
            for(int k=0; k<matrixRow; k++) {
                result(i,j) += (this->m_vec[m_cols*i+k]) * (other.m_vec[matrixCol*k+j]);
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
    // Implementation goes here
    int matrixRow = other.m_rows;
    int matrixCol = other.m_cols;
    Matrix<T>result(matrixRow,matrixCol);
    for (int row=0; row<other.m_rows; row++) {

        for (int col=0; col<other.m_cols; col++) {
            result(row,col) = this->m_vec[m_cols*row+col] + other.m_vec[m_cols*row+col];
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
    // Implementation goes here
    int matrixRow = other.m_rows;
    int matrixCol = other.m_cols;
    Matrix<T>result(matrixRow,matrixCol);
    for (int row=0; row<other.m_rows; row++) {
        for (int col=0; col<other.m_cols; col++) {
            result(row,col) = this->m_vec[m_cols*row+col] - other.m_vec[m_cols*row+col];
        }
    }
    return result;
}

template<typename T>
Matrix<T>operator+(const T & lhs, const Matrix<T> & rhs) {
    T scalar = lhs;
    int matrixRow = rhs.rows();
    int matrixCol = rhs.cols();
    Matrix<T>result(matrixRow,matrixCol);
    for (int row=0; row<matrixRow; row++) {
        for (int col=0; col<matrixCol; col++) {
            result(row,col) = rhs(row, col) + lhs;
        }
    }
    return result;
}

template<typename T>
Matrix<T>operator-(const T & lhs, const Matrix<T> & rhs) {
    T scalar = lhs;
    int matrixRow = rhs.rows();
    int matrixCol = rhs.cols();
    Matrix<T>result(matrixRow,matrixCol);
    for (int row=0; row<matrixRow; row++) {
        for (int col=0; col<matrixCol; col++) {
            result(row,col) = rhs(row, col) - lhs;
        }
    }
    return result;
}

template<typename T>
Matrix<T>operator*(const T & lhs, const Matrix<T> & rhs) {
    T scalar = lhs;
    int matrixRow = rhs.rows();
    int matrixCol = rhs.cols();
    Matrix<T>result(matrixRow,matrixCol);
    for (int row=0; row<matrixRow; row++) {
        for (int col=0; col<matrixCol; col++) {
            result(row,col) = rhs(row, col) * lhs;
        }
    }
    return result;
}

//matris och skalär *
template<typename T>
Matrix<T>operator*=(Matrix<T> & rhs, const T & lhs) {
    Matrix<T>result(rhs.rows(), rhs.cols());
    for(int i = 0; i < rhs.rows(); i++){
        for(int j = 0; j < rhs.cols(); j++){
            result(i,j) = rhs(i,j) * lhs;
        }
    }
    rhs = result;
}

//matris och skalär +
template<typename T>
Matrix<T>operator+=(Matrix<T> & rhs, const T & lhs) {
    Matrix<T>result(rhs.rows(), rhs.cols());
    for(int i = 0; i < rhs.rows(); i++){
        for(int j = 0; j < rhs.cols(); j++){
            result(i,j) = rhs(i,j) + lhs;
        }
    }
    rhs = result;
}

//matris och skalär -
template<typename T>
Matrix<T>operator-=(Matrix<T> & rhs, const T & lhs) {
    Matrix<T>result(rhs.rows(), rhs.cols());
    for(int i = 0; i < rhs.rows(); i++){
        for(int j = 0; j < rhs.cols(); j++){
            result(i,j) = rhs(i,j) - lhs;
        }
    }
    rhs = result;
}

//två matriser
template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) {
    // Implementation goes here
    Matrix<T>result(m_rows, other.m_cols);
    result = (*this) * other;
    *this = result;
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
    Matrix<T>result(m_rows, other.m_cols);
    result = (*this) + other;
    *this = result;
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
    Matrix<T>result(m_rows, other.m_cols);
    result = (*this) - other;
    *this = result;
}
//iteratorer
template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return &m_vec[0];
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    T length = sizeof(m_vec);
    T * myPointer = (&m_vec[0] + length);
    return myPointer;

}

template<typename T>
void Matrix<T>::insert_row(size_t row) {
    int old_rows = m_rows;
    int old_cols = m_cols;
    T * new_vec = new T[old_rows*old_cols+old_cols];
    //cout << old_rows << endl;
    //cout << old_cols << endl;
    //cout << old_rows*old_cols + old_cols << endl;
    bool passed = false;

    for(int i = 0; i < old_rows*old_cols + old_cols;){
        if(i == old_cols*row){
            for(int j = 0; j < old_cols; j++){
                passed = true;
                //cout << "en nolla: ";
                //cout << old_cols*row+j << endl;
                new_vec[old_cols*row+j] = 0;
                i++;
            }
        }
        else{
            //cout <<"ett kopierat i : " << i << endl;
            if(passed){
                new_vec[i] = m_vec[i-old_cols];
                i++;
            }
            else{
                new_vec[i] = m_vec[i];
                i++;
            }
        }
    }
    delete[] this-> m_vec;
    this-> m_vec = new_vec;
    m_rows = m_rows + 1;
}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    int old_rows = m_rows;
    int old_cols = m_cols;
    T * new_vec = new T[old_rows*old_cols+old_cols];
    bool passed = false;

    for(int i = 0; i < old_rows*old_cols + old_cols;){
        if(i == old_cols*row+old_cols){
            for(int j = 0; j < old_cols; j++){
                passed = true;
                //cout << "en nolla: ";
                //cout << old_cols*row+j << endl;
                new_vec[old_cols*row+j+old_cols] = 0;
                i++;
            }
        }
        else{
            //cout <<"ett kopierat i : " << i << endl;
            if(passed){
                new_vec[i] = m_vec[i-old_cols];
                i++;
            }
            else{
                new_vec[i] = m_vec[i];
                i++;
            }
        }
    }
    delete[] this-> m_vec;
    this-> m_vec = new_vec;
    m_rows = m_rows + 1;
}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    int old_rows = m_rows;
    int old_cols = m_cols;
    //cout << old_rows << endl;
    //cout << old_cols << endl;
    //cout << old_rows*old_cols - old_cols << endl;
    T * new_vec = new T[old_rows*old_cols-old_cols];
    bool passed = false;

    for(int i = 0; i < old_rows*old_cols;){
        if(i == old_cols*row){
            for(int j = 0; j < old_cols; j++){
                passed = true;
                //cout << "en nolla: ";
                //cout << old_cols*row << endl;
                i++;
            }
        }
        else{
            //cout <<"ett kopierat i : " << i << endl;
            //cout << "där new[i] = mvec[i+old_cols]" << endl;
            if(passed){
                new_vec[i-old_cols] = m_vec[i];
                i++;
            }
            else{
                new_vec[i] = m_vec[i];
                i++;
            }
        }
    }
    delete[] this-> m_vec;
    this-> m_vec = new_vec;
    this->m_rows = m_rows - 1;
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    int old_rows = m_rows;
    int old_cols = m_cols;
    T * new_vec = new T[old_rows*old_cols + old_rows];
    bool passed = false;
    int k = 0;
    int l = 0;

    for(int i = 0; i < old_rows*old_cols;){
        if(i == col + k*(old_cols)){
            // + k*old_cols
                //cout << "newvec en nolla: ";
                //cout << i+l << endl;
                //new_vec[(old_cols+1)*j + col] = 0;
                new_vec[i+l] = 0;
        k++;
        //i++;
        l++;
        }
        else{
            //cout <<"ett kopierat i : " << i << endl;
                new_vec[i+l] = m_vec[i];
                //cout << "else: ";
                //cout << "la m_vec "<< i << "inuti " << i+l <<endl;
                i++;
        }
            
    }
    delete[] this-> m_vec;
    this-> m_vec = new_vec;
    m_cols = m_cols + 1;
}


template<typename T>
void Matrix<T>::append_column(size_t col) {
    int old_rows = m_rows;
    int old_cols = m_cols;
    T * new_vec = new T[old_rows*old_cols + old_rows];
    bool passed = false;
    int k = 0;
    int l = 0;

    for(int i = 0; i < old_rows*old_cols;){
        if(i == col + 1 + k*(old_cols)){
            // + k*old_cols
                //cout << "newvec en nolla: ";
                //cout << i+l << endl;
                //new_vec[(old_cols+1)*j + col] = 0;
                new_vec[i+l] = 0;
        k++;
        //i++;
        l++;
        }
        else{
            //cout <<"ett kopierat i : " << i << endl;
                new_vec[i+l] = m_vec[i];
                //cout << "else: ";
                //cout << "la m_vec "<< i << "inuti " << i+l <<endl;
                i++;
        }
            
    }
    delete[] this-> m_vec;
    this-> m_vec = new_vec;
    m_cols = m_cols + 1;
}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    int old_rows = m_rows;
    int old_cols = m_cols;
    T * new_vec = new T[old_rows*old_cols - old_rows];
    bool passed = false;
    int k = 0;
    int l = 0;

    for(int i = 0; i < old_rows*old_cols;){
        if(i == col + k*(old_cols)){
            // + k*old_cols
                //cout << "ta bort: ";
                //cout << col + k*(old_cols) << endl;
                //new_vec[(old_cols+1)*j + col] = 0;
                //new_vec[i+l] = 0;
            k++;
            i++;
            l++;
        }
        else{
            //cout <<"ett kopierat i : " << i << endl;
                new_vec[i-l] = m_vec[i];
                //cout << "else: ";
                //cout << "la m_vec "<< i << " inuti newvec " << i-l <<endl;
                i++;
        }
            
    }
    delete[] this-> m_vec;
    this-> m_vec = new_vec;
    m_cols = m_cols - 1;

}

template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
    int n = 0;
    int i = 0;
    int rows = m.rows();
    int cols = m.cols();
    T * new_vec = new T[rows*cols];
    string tp;

    while(getline(is, tp, ' ')){
        tp.erase(remove(tp.begin(), tp.end(), '\n'), tp.end());
        if (std::is_same<T, int>::value){
            //cout << tp << endl;
            int num = stoi(tp);
            new_vec[i] = num;
            //cout << new_vec[i] << endl;
            i++;
        }
        else if(std::is_same<T, float>::value){
            float num = stof(tp);
            new_vec[i] = num;
            //cout << new_vec[i] << endl;
            i++;
        }
        else{
            //char
            char typechar = tp[0];
            new_vec[i] = typechar;
            cout << new_vec[i] << endl;
            i++;
        }
    }
    for(int k = 0; k < rows; k++){
        for(int l = 0; l < cols; l++){
            m(k,l) = new_vec[n];
            n++;
        }
    }
    delete[] new_vec;
    return is;

}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    for(int i = 0; i < m.rows(); i++){
        if(i != 0){
            os << '\n';
        }
        for(int j = 0; j < m.cols(); j++){
            os << m(i,j) << " ";
        }
    }
    return os;
}
#endif //MATRIX_H
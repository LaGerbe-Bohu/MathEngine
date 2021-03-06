
// QUATERNION
class Quaternion;

template<int N,int M>
class Matrix{
    float tab[N*M];

public:
    Matrix(float t[N*M] ) {

        /* A CHANGER */
        for (int i = 0; i < N ; ++i) {
            for (int j = 0; j < M; ++j) {
                tab[(i*N)+j] = t[(i*N)+j];
                // std::cout << tab[i][j] << " | i : " << i << " j  :"<< j;
            }
            //  std::cout << std::endl;
        }
    }

    Matrix(int t[N*M] ) {

        /* A CHANGER */
        for (int i = 0; i < N ; ++i) {
            for (int j = 0; j < M; ++j) {
                tab[(i*N)+j] = t[(i*N)+j];
            }
        }
    }

    Matrix(){
        for (int i = 0; i < N ; ++i) {
            for (int j = 0; j < M; ++j) {
                tab[i*j] = 0;
                if(i == j){
                    tab[(i*N)+ i] = 1;
                }
            }
        }
    };

    float* getTab(){
        return this->tab;
    }

    float setAt(int i,int j,int v){
       return  tab[(i*N)+j] = v;
    }

    float getAt(int i,int j){
        return tab[(i*N)+j] ;
    }

    void display (){
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                std::cout<<tab[i*N + j] << " ";
            }
            std::cout  << std::endl;
        }

    }

    float operator()(int i,int j ){
        return tab[(i*N)+j];
    }
};



class Quaternion{
    float tab[4]{};
    float*  norme;
    float* conjTab;
    public:
    Quaternion(float x,float y,float z,float w){
        tab[0] = x;
        tab[1] = y;
        tab[2] = z;
        tab[3] = w;
    }

    Quaternion(float axe[3],float angle){

        angle = (angle/2) * 3.14159 / 180.0;

        tab[0] = axe[0] * sinf(angle);
        tab[1] = axe[1] * sinf(angle);
        tab[2] =  axe[2]* sinf(angle);
        tab[3] = cosf(angle);

    }

    explicit Quaternion(const float _f[4]){
        for (int i = 0; i < (int)sizeof(tab)/sizeof(int); ++i) {
            tab[i] = _f[i];
        }
    }


    float* getTab(){
        return tab;
    }

    float getNorm(){
        return sqrtf(powf(tab[0],2) + powf(tab[1],2) + powf(tab[2],2)  + powf(tab[3],2)  );
    }

    float* getQutrnormalized(){
        float norm = this->getNorm();

        this->norme = new float[4] {tab[0] / norm, tab[1] / norm, tab[2] / norm, tab[3] / norm };

        return this->norme;
    }



    void normalize(){
        float* tb = this->getQutrnormalized();
        this->tab[0] = tb[0];
        this->tab[1] = tb[1];
        this->tab[2] = tb[2];

    }


    float* conj(){

        this->conjTab = new float[4] {-tab[0] , -tab[1] , -tab[2] , tab[3]  };
        return  this->conjTab;
    }

    void QuaternionDeconstru(){
        delete norme;
        delete conjTab;
    }



    float dot(Quaternion qtr){
        return (this->tab[0]*qtr.tab[0]) + (this->tab[1]*qtr.tab[1]) + (this->tab[2]*qtr.tab[2]) + (this->tab[3]*qtr.tab[3]);
    }

    float* CrossProduct(Quaternion qtr){
        static float t [3] {
            this->tab[1]*qtr.tab[2] -  this->tab[2]*qtr.tab[1],
            this->tab[2]*qtr.tab[0] -  this->tab[0]*qtr.tab[2],
            this->tab[0]*qtr.tab[1] -  this->tab[1]*qtr.tab[0]
        };

        return t;
    }


    Matrix<4,4> getRotationMatrix(){

        Quaternion q(this->getQutrnormalized());

        float a = q.tab[3];
        float b = q.tab[0];
        float c = q.tab[1];
        float d = q.tab[2];

        float tmp[4*4] {
                1-(2*powf(c,2)) - 2*powf(d,2), 2*b*c + 2*d*a , 2*b*d - 2*c*a,0,
                2*b*c - 2*d*a, 1 - 2*powf(b,2) - 2*powf(d,2), 2*c*d + 2*b*a,0,
                2*b*d + 2*c*a, 2*c*d - 2*b*a , 1 - 2*powf(b,2) - 2*powf(c,2),0,
                0.0,0.0,0,1.0f
        };

        Matrix<4,4> m(tmp);

        return  m;
    }



    Quaternion operator*=(Quaternion qtr){
        float q[4];

        q[3] = (this->tab[3]*qtr.tab[3]) - (this->tab[0]*qtr.tab[0]) - (this->tab[1]*qtr.tab[1]) - (this->tab[2] * qtr.tab[2]);
        q[0] = (this->tab[3] * qtr.tab[0]) + (this->tab[0]*qtr.tab[3]) + (this->tab[1] * qtr.tab[2]) - (this->tab[2] * qtr.tab[1]);
        q[1] = (this->tab[3]*qtr.tab[1]) - (this->tab[0] * qtr.tab[2]) + (this->tab[1]*qtr.tab[3]) + (this->tab[2] * qtr.tab[0]);
        q[2] = (this->tab[3]*qtr.tab[2]) + (this->tab[0] * qtr.tab[1]) - (this->tab[1]*qtr.tab[0]) + (this->tab[2] * qtr.tab[3]);

        return Quaternion(q);
    }

    Quaternion operator*(Quaternion qtr){
        return *this*=qtr;
    }


    Quaternion operator+=(Quaternion qtr){

        return {this->tab[0] + qtr.tab[0],this->tab[1] + qtr.tab[1],this->tab[2] + qtr.tab[2],this->tab[3] + qtr.tab[3]};
    }

    Quaternion operator+(Quaternion qtr){
        return *this+=qtr;
    }

    Quaternion operator-=(Quaternion qtr){

        return {this->tab[0] - qtr.tab[0],this->tab[1] - qtr.tab[1],this->tab[2] - qtr.tab[2],this->tab[3] - qtr.tab[3]};
    }

    Quaternion operator-(Quaternion qtr){
        return *this-=qtr;
    }


};



template<int N, int M,int O,int P>
Matrix<N,P> multMatrice(Matrix<N,M> m1,Matrix<O,P> m2){
    Matrix<N,P> m;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            m.setAt(i,j,0);

            for (int k = 0; k < P; k++) {
                m.setAt(i,j, m(i,j) + m1(i,k) * m2(k,j));
            }
        }
    }

    return m;
}



template<int N,int M>
std::ostream& operator<<(std::ostream& os, Matrix<N,M> _m){


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            os<< _m(i,j) << " ";
        }
        os  << std::endl;
    }

    return os;
}


std::ostream& operator<<(std::ostream& os, Quaternion q){
    float * tab = &q.getTab()[0];

    return os << " x : " << tab[0] << " y : " << tab[1] << " z : " << tab[2] << " w : " <<tab[3] << std::endl;
}



Quaternion getQuaternion(Matrix<4,4> mat) {
    float w = sqrtf(1.0 +  mat.getAt(0,0) + mat.getAt(1,1) + mat.getAt(2,2) )/ 2.0;
    float w4 = (4.0 * w);
    float x = ( mat.getAt(2,1) - mat.getAt(1,2) )/ w4;
    float y = ( mat.getAt(0,2) - mat.getAt(2,0) )/ w4;
    float z = ( mat.getAt(1,0) - mat.getAt(0,1) )/ w4;
    Quaternion t(x,-y,z,w);
    return  t;
}


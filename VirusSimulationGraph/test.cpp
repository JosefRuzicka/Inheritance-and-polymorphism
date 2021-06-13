#include "pch.h"
#include "..//LabGui3_Sam_Josef/RedNodos.h "
#include "..//LabGui3_Sam_Josef/Nodo.h "

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

class PruebasLabGui3 : public ::testing::Test {
protected:
    /* DATOS COMUNES A CASOS DE PRUEBA */
    RedNodos red;
    RedNodos red2;
    RedNodos red3;
    ifstream archivo;
    // Constructor inicializador del suite de pruebas.
    PruebasLabGui3();
    // Destructor del suite de pruebas.
    ~PruebasLabGui3() override;
    /* INICIALIZACION DE LAS PRUEBAS, puede eliminarse si no se usa.*/
    // se invoca al iniciar cada prueba del accesorio.
    void SetUp() override;
    /* FINALIZACION DE LAS PRUEBAS, puede eliminarse si no se usa*/
    // se invoca al finalizar cada prueba del accesorio.
    void TearDown() override;

};
/* DEFINICION DE LOS METODOS BASICOS DEL ACCESORIO*/

PruebasLabGui3::PruebasLabGui3() : red(100, 0.3), red2(100, 1), red3(100, -1)
{
    string numero_S;
    ifstream archivo("archivo_experimentos.txt", ios::in);
    archivo.open("archivo_experimentos.txt");//Abrir el archivo para leer

    if (!archivo) {
        cout << "no encuentra el archivo de datos" << endl;

    }
    else {
        getline(archivo, numero_S, ',');
    }
}
PruebasLabGui3::~PruebasLabGui3()
{

}
void PruebasLabGui3::SetUp()
{
    // Se invoca despues del constructor, antes de cada caso de prueba.

}
void PruebasLabGui3::TearDown()

{

}
/* CASOS DE PRUEBA */

// EFE: Verifica la creacion correcta de las redes.
TEST_F(PruebasLabGui3, constructorAleatorio_t) {
    RedNodos redPrueba = RedNodos(10, 0.5);
    int nodoAleatorio = rand() % 10;
    EXPECT_TRUE(redPrueba.obtCntVrtAdys(nodoAleatorio) > 2);
}

// EFE: Verifica la creacion correcta de las redes.
TEST_F(PruebasLabGui3, constructorAleatorio_2f) {
    RedNodos redPrueba = RedNodos(100, 0.3);
    int nodoAleatorio = rand() % 10;
    EXPECT_FALSE(redPrueba.obtCntVrtAdys(nodoAleatorio) > 70);
}

// EFE: Verifica la creacion correcta de los vrts
TEST_F(PruebasLabGui3, xstVrt1_t)
{
    EXPECT_TRUE(red.xstVrt(18));
};

// EFE: Verifica la creacion correcta de los vrts
TEST_F(PruebasLabGui3, xstVrt1_f)
{
    EXPECT_FALSE(red.xstVrt(100));
};

// EFE: Verifica la creacion correcta de los adys
TEST_F(PruebasLabGui3, xstAdy1_t)
{
    EXPECT_TRUE(red2.xstAdy(13, 14));
};

// EFE: Verifica la creacion correcta de los adys
TEST_F(PruebasLabGui3, xstAdy1_f)
{
    EXPECT_FALSE(red3.xstAdy(13, 14));
};

// EFE: Verifica la obtencion correcta de los adys
TEST_F(PruebasLabGui3, obtIdVrtAdys1_t)
{
    vector<int> vectorAdys;
    red3.obtIdVrtAdys(13, vectorAdys);
    EXPECT_TRUE(vectorAdys.size() == 0);
};

// EFE: Verifica la obtencion correcta de los adys
TEST_F(PruebasLabGui3, obtIdVrtAdys2_t)
{
    vector<int> vectorAdys;
    red2.obtIdVrtAdys(13, vectorAdys);
    EXPECT_TRUE(vectorAdys.size() == 99);
};

// EFE:  Verifica la obtencion correcta de los adys.
TEST_F(PruebasLabGui3, obtIdVrtAdys3_t) {
    vector<int> vectorAdys;
    vectorAdys.push_back(1);
    red3.obtIdVrtAdys(1, vectorAdys);
    EXPECT_TRUE(vectorAdys.at(0) == 1);
}

// EFE: Verifica la obtencion correcta de la cantidad de adys
TEST_F(PruebasLabGui3, obtCntVrtAdys1_t)
{
    EXPECT_TRUE(red2.obtCntVrtAdys(18) == 99);
};

// EFE: Verifica la obtencion correcta de la cantidad de adys
TEST_F(PruebasLabGui3, obtCntVrtAdys2_f)
{
    EXPECT_FALSE(red3.obtCntVrtAdys(82) == 99);
};

// EFE:  Verifica la obtencion correcta de los adys.
TEST_F(PruebasLabGui3, obtCntVrtAdys3_t) {
    vector<int> vectorAdys;
    vectorAdys.push_back(1);
    red3.obtIdVrtAdys(1, vectorAdys);
    EXPECT_TRUE(vectorAdys.at(0) == 1);
}

// EFE: Verifica la obtencion correcta de la cantidad total de vrts
TEST_F(PruebasLabGui3, obtTotVrt1_T)
{
    EXPECT_TRUE(red.obtTotVrt() == 100);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts
TEST_F(PruebasLabGui3, obtTotVrt1_F)
{
    EXPECT_FALSE(red.obtTotVrt() == 99);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Susceptibles
TEST_F(PruebasLabGui3, obtTotVrtSusceptibles1_T)
{
    EXPECT_TRUE(red.obtTotVrtSusceptibles() == 100);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Susceptibles
TEST_F(PruebasLabGui3, obtTotVrtSusceptibles1_F)
{
    EXPECT_FALSE(red.obtTotVrtSusceptibles() == 50);
};


// EFE: Verifica la obtencion correcta de la cantidad total de vrts Infectado
TEST_F(PruebasLabGui3, obtTotVrtInfectados1_T)
{
    EXPECT_TRUE(red.obtTotVrtInfectados() == 0);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Infectado
TEST_F(PruebasLabGui3, obtTotVrtInfectados1_F)
{
    EXPECT_FALSE(red.obtTotVrtInfectados() == 12);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Resistentes
TEST_F(PruebasLabGui3, obtTotVrtResistentes1_T)
{
    EXPECT_TRUE(red.obtTotVrtResistentes() == 0);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Resistentes
TEST_F(PruebasLabGui3, obtTotVrtResistentes1_F)
{
    EXPECT_FALSE(red.obtTotVrtResistentes() == 1);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Resistentes
TEST_F(PruebasLabGui3, operador_T)
{
    int estado = red[31].obtEstado();
    EXPECT_TRUE(estado == 0);
};

// EFE: Verifica la obtencion correcta de la cantidad total de vrts Resistentes
TEST_F(PruebasLabGui3, operador_2T)
{
    int estado = red[31].obtEstado();
    red[31].modEstado(Nodo::I);
    estado = red[31].obtEstado();
    EXPECT_TRUE(estado == 1);
};

// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Resistentes
TEST_F(PruebasLabGui3, obtPrcVrtResistentes1_T)
{
    EXPECT_TRUE(red.obtPrcVrtResistentes() == 0);
};

// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Resistentes
TEST_F(PruebasLabGui3, obtPrcVrtResistentes2_T)
{
    RedNodos redPrueba = RedNodos(10, 0.5);
    EXPECT_TRUE(redPrueba.obtPrcVrtResistentes() == 0);
};

// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Resistentes
TEST_F(PruebasLabGui3, obtPrcVrtResistentes1_F)
{
    EXPECT_FALSE(red.obtPrcVrtResistentes() == 0.5);
};

// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Susceptibles
TEST_F(PruebasLabGui3, obtPrcVrtSusceptibles1_F)
{
    EXPECT_FALSE(red.obtPrcVrtSusceptibles() == 0.9);
};

// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Susceptibles
TEST_F(PruebasLabGui3, obtPrcVrtSusceptibles1_T)
{
    EXPECT_TRUE(red.obtPrcVrtSusceptibles() == 1);
};


// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Infectados
TEST_F(PruebasLabGui3, obtPrcVrtInfectados1_T)
{
    EXPECT_TRUE(red.obtPrcVrtInfectados() == 0);
};

// EFE: Verifica la obtencion correcta de la cantidad porcentual de vrts Infectados
TEST_F(PruebasLabGui3, obtPrcVrtInfectados1_F)
{
    EXPECT_FALSE(red.obtPrcVrtInfectados() == 0.3);
};
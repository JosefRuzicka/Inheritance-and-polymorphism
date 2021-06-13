#include "pch.h"
#include "C:\Users\Josef\source\repos\Lab1_Josef_Sam\Lab1_Josef_Sam\TableroReversiHex.h"
#include "C:\Users\Josef\source\repos\Lab1_Josef_Sam\Lab1_Josef_Sam\LstAdys.h"

/**
* Clase de google test, se debe hace Public todo en las clases TableroReversiHex.h y LstAdys.h, verifica que los métodos funcionen correctamente
*
* Authors Josef Ruzicka y Samantha Romero, con código base del profesor Alan Calderón
* version 3.0
* since   2020-04-05
*/

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

class PruebasLab1 : public ::testing::Test {
protected:
    /* DATOS COMUNES A CASOS DE PRUEBA */
    TableroReversiHex trp5;
    TableroReversiHex trp7;
    TableroReversiHex trp_anulado5;
    TableroReversiHex trp_anulado7;
    // Constructor inicializador del suite de pruebas.
    PruebasLab1();
    // Destructor del suite de pruebas.
    ~PruebasLab1() override;
    /* INICIALIZACION DE LAS PRUEBAS, puede eliminarse si no se usa.*/
    // se invoca al iniciar cada prueba del accesorio.
    void SetUp() override;
    /* FINALIZACION DE LAS PRUEBAS, puede eliminarse si no se usa*/
    // se invoca al finalizar cada prueba del accesorio.
    void TearDown() override;
 
};
/* DEFINICION DE LOS METODOS BASICOS DEL ACCESORIO*/

PruebasLab1::PruebasLab1() :trp5(5), trp7(7), trp_anulado5(5), trp_anulado7(7)
{

}
PruebasLab1::~PruebasLab1()
{

}
void PruebasLab1::SetUp()
{
    // Se invoca despues del constructor, antes de cada caso de prueba.
    trp_anulado5.colocarSimple(3, 1, TableroReversiHex::nula);
    trp_anulado5.colocarSimple(0, 2, TableroReversiHex::nula);
    trp_anulado5.colocarSimple(3, 2, TableroReversiHex::nula);
    trp_anulado5.colocarSimple(1, 1, TableroReversiHex::nula);
    trp_anulado5.colocarSimple(4, 2, TableroReversiHex::nula);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::nula);


    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::nula);
    trp_anulado7.colocarSimple(3, 3, TableroReversiHex::nula);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::nula);
    trp_anulado7.colocarSimple(2, 3, TableroReversiHex::nula);


}
void PruebasLab1::TearDown()

{

}
/* CASOS DE PRUEBA */

// EFE: Valida la inicialización correcta que hace el constructor de TableroReversi.
// Además indirectamente valida el método verFichaEn().
TEST_F(PruebasLab1, InicializacionCorrecta1)
{
    //Pruebas para el tablero que inicia con 6 fichas
    ASSERT_EQ(trp5.verFichaEn(3, 1), TableroReversiHex::negra);
    ASSERT_EQ(trp5.verFichaEn(0, 2), TableroReversiHex::negra);
    ASSERT_EQ(trp5.verFichaEn(3, 2), TableroReversiHex::negra);
    ASSERT_EQ(trp5.verFichaEn(1, 1), TableroReversiHex::blanca);
    ASSERT_EQ(trp5.verFichaEn(4, 2), TableroReversiHex::blanca);
    ASSERT_EQ(trp5.verFichaEn(1, 2), TableroReversiHex::blanca);

    ASSERT_EQ(trp5.verFichaEn(0, 1), TableroReversiHex::nula);
    ASSERT_EQ(trp5.verFichaEn(0, 3), TableroReversiHex::nula);
    ASSERT_EQ(trp5.verFichaEn(4, 4), TableroReversiHex::nula);
    ASSERT_EQ(trp5.verFichaEn(3, 3), TableroReversiHex::nula);
    ASSERT_EQ(trp5.verFichaEn(2, 3), TableroReversiHex::nula);
    ASSERT_EQ(trp5.verFichaEn(2, 2), TableroReversiHex::nula);
    
   for (int p = 0; p < 5; p++) {
         for (int c = 0; c < 5; c++) {
              if ( c < 5 && p < 5 && !((p == 1) && (c == 3)) && !((p == 2)
                    && (c == 0)) && !((p == 2) && (c == 3)) && !((p == 1)
                    && (c == 1)) && !((p == 2) && (c == 1)) && !((p == 2) && (c == 4))
                    && !((c == 1) && (p == 4)) && !(c==3) && (p == 4)) {
                    ASSERT_EQ(trp5.verFichaEn(c, p), TableroReversiHex::nula);
               }
         }
   }
};
// EFE: Valida la inicialización correcta que hace el constructor de TableroReversi.
// Además indirectamente valida el método verFichaEn().
TEST_F(PruebasLab1, InicializacionCorrecta2)
{
    //Pruebas para el tablero que inicia con 4 fichas
    ASSERT_EQ(trp7.verFichaEn(4, 3), TableroReversiHex::blanca);
    ASSERT_EQ(trp7.verFichaEn(3, 3), TableroReversiHex::blanca);
    ASSERT_EQ(trp7.verFichaEn(3, 2), TableroReversiHex::negra);
    ASSERT_EQ(trp7.verFichaEn(2, 3), TableroReversiHex::negra);

    for (int p = 0; p < 7; p++)
        for (int c = 0; c < 7; c++)
            if (c < 7 && p < 7 && !((p == 3) && (c == 4)) && !((p == 3)
                && (c == 3)) && !((p == 2) && (c == 3))
                && !((p == 3) && (c == 2)) && !((c == 1)
                    && (p == 6)) && !((c == 3) && (p == 6)) && !((c == 5) && (p == 6)))
                ASSERT_EQ(trp7.verFichaEn(c, p), TableroReversiHex::nula);
};
// EFE: Valida la colocación correcta de fichas negras, blancas así como anulación,
// en posiciones seleccionadas del tablero.
TEST_F(PruebasLab1, ColocacionFichaCorrecta)
{
    trp5.colocarSimple(0, 0, TableroReversiHex::Ficha::negra);
    trp5.colocarSimple(3, 3, TableroReversiHex::Ficha::blanca);
    trp5.colocarSimple(0, 3, TableroReversiHex::Ficha::nula);
    trp5.colocarSimple(3, 0, TableroReversiHex::Ficha::nula);
    EXPECT_EQ(trp5.verFichaEn(0, 0), TableroReversiHex::Ficha::negra);
    EXPECT_EQ(trp5.verFichaEn(3, 3), TableroReversiHex::Ficha::blanca);
    EXPECT_EQ(trp5.verFichaEn(0, 3), TableroReversiHex::Ficha::nula);
    EXPECT_EQ(trp5.verFichaEn(3, 0), TableroReversiHex::Ficha::nula);
};
// EFE: Prueba verFlanqueaDir(), variante #1-false, dirección 1.
TEST_F(PruebasLab1, verFlanqueaDir_1_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,2,blanca).
    trp_anulado5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);
    // la (2,2) es la que se intenta validar
    EXPECT_FALSE(trp_anulado5.verFlanqueaDir(1, 2, 2, TableroReversiHex::Ficha::negra));
}

// EFE: Prueba verFlanqueaDir(), variante #2-false, dirección 1.
TEST_F(PruebasLab1, verFlanqueaDir_2_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (6,3,blanca).
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    // la (4, 3) se deja anulada
    // la (6, 3) es la que se intenta validar

    EXPECT_FALSE(trp_anulado7.verFlanqueaDir(1, 6, 3, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #3-False, dirección 4.
TEST_F(PruebasLab1, verFlanqueaDir_3_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,3,blanca).
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    //trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    // la (2,3,blanca) es la que se intenta validar

    EXPECT_FALSE(trp_anulado5.verFlanqueaDir(4, 2, 3, TableroReversiHex::Ficha::negra));
}
// EFE: Prueba verFlanqueaDir(), variante #4-false, dirección 4.
TEST_F(PruebasLab1, verFlanqueaDir_4_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (0,4,blanca).
    trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    //trp_anulado7.colocarSimple(4, 4, TableroReversiHex::Ficha::negra);
    // la(2, 4) se deja anulada
    // la (0,4,blanca) es la que se intenta validar

    EXPECT_FALSE(trp_anulado7.verFlanqueaDir(4, 0, 4, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #5-false, dirección 0.
TEST_F(PruebasLab1, verFlanqueaDir_5_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,1,blanca).
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    // la (3, 1) se deja anulada
    // la (4,1) es la que se intenta validar
    EXPECT_FALSE(trp_anulado5.verFlanqueaDir(0, 4, 1, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #6-true, dirección 0.
TEST_F(PruebasLab1, verFlanqueaDir_6_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,3,blanca).
    trp_anulado7.colocarSimple(0, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
    //trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 1, TableroReversiHex::Ficha::blanca);
    // la (2,3,blanca) es la que se intenta validar

    EXPECT_TRUE(trp_anulado7.verFlanqueaDir(0, 2, 3, TableroReversiHex::Ficha::blanca));
}

// EFE: Prueba verFlanqueaDir(), variante #7-true, dirección 2.
TEST_F(PruebasLab1, verFlanqueaDir_7_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (1,1,blanca).
    trp_anulado5.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    //trp_anulado5.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    // la (1,1) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.verFlanqueaDir(2, 1, 1, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #8-true, dirección 2.
TEST_F(PruebasLab1, verFlanqueaDir_8_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (1,1,blanca).
    trp_anulado7.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    // trp_anulado7.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    // la (1,1,blanca) es la que se intenta validar

    EXPECT_TRUE(trp_anulado7.verFlanqueaDir(2, 1, 1, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #9-true, dirección 5.
TEST_F(PruebasLab1, verFlanqueaDir_9_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,1,blanca).
    trp_anulado5.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);
    // trp_anulado5.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
    // la (3,1) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.verFlanqueaDir(5, 3, 1, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #10-false, dirección 5.
TEST_F(PruebasLab1, verFlanqueaDir_10_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,2,blanca).
    trp_anulado7.colocarSimple(6, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
    // la(0, 0) se deja anulada
    // la (4,2,blanca) es la que se intenta validar

    EXPECT_FALSE(trp_anulado7.verFlanqueaDir(5, 4, 2, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #11-true, dirección 3.
TEST_F(PruebasLab1, verFlanqueaDir_11_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,1,blanca).
    trp_anulado5.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
    // trp_anulado5.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
    // la (2,1) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.verFlanqueaDir(3, 2, 1, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba verFlanqueaDir(), variante #12-true, dirección 3.
TEST_F(PruebasLab1, verFlanqueaDir_12_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,1,blanca).
    trp_anulado7.colocarSimple(6, 0, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 0, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 1, TableroReversiHex::Ficha::negra);
    //trp_anulado7.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    // la (3,1,blanca) es la que se intenta validar

    EXPECT_TRUE(trp_anulado7.verFlanqueaDir(3, 3, 1, TableroReversiHex::Ficha::blanca));
}

// EFE: Prueba validarJugada(), variante #1-true.

TEST_F(PruebasLab1, validarJugada_1_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,2,blanca).
   // trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 1, TableroReversiHex::Ficha::blanca);
    // la (2,2) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.validarJugada(2, 2, TableroReversiHex::Ficha::blanca));
}

// EFE: Prueba validarJugada(), variante #2-true.
TEST_F(PruebasLab1, validarJugada_2_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,2,blanca).
   // trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 1, TableroReversiHex::Ficha::blanca);
    // la (3,2,blanca) es la que se intenta validar
    EXPECT_TRUE(trp_anulado7.validarJugada(3, 2, TableroReversiHex::Ficha::blanca));
}


// EFE: Prueba validarJugada(), variante #3-true, 2 direecciones.
TEST_F(PruebasLab1, validarJugada_3_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,2,blanca).
     // trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    // la (2,2) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.validarJugada(2, 2, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba validarJugada(), variante #4-true, 2 direcciones.
TEST_F(PruebasLab1, validarJugada_4_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,2,blanca).
   // trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    // la (3,2,blanca) es la que se intenta validar
    EXPECT_TRUE(trp_anulado7.validarJugada(3, 2, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba validarJugada(), variante #5-true, 2 direcciones.
TEST_F(PruebasLab1, validarJugada_5_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (0,2,blanca).
     // trp_anulado5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(3, 3, TableroReversiHex::Ficha::blanca);
    // la (0,2) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.validarJugada(0, 2, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba validarJugada(), variante #6-true.
TEST_F(PruebasLab1, validarJugada_6_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (0,3,blanca).
   // trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 5, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 5, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 6, TableroReversiHex::Ficha::blanca);
    // la (0,3,blanca) es la que se intenta validar
    EXPECT_TRUE(trp_anulado7.validarJugada(0, 3, TableroReversiHex::Ficha::blanca));
}
// EFE: Prueba validarJugada(), variante #7-true, 2 direcciones.
TEST_F(PruebasLab1, validarJugada_7_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,3,blanca).
     // trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(1, 1, TableroReversiHex::Ficha::blanca);
    // la (4,3) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.validarJugada(4, 3, TableroReversiHex::Ficha::blanca));
}


// EFE: Prueba validarJugada(), variante #8-true, 2 direcciones.
TEST_F(PruebasLab1, validarJugada_8_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (6,4,blanca).
   // trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    // la (6,4,blanca) es la que se intenta validar
    EXPECT_TRUE(trp_anulado7.validarJugada(6, 4, TableroReversiHex::Ficha::blanca));
}

// EFE: Prueba validarJugada(), variante #9-false no hay flanqueo.
TEST_F(PruebasLab1, validarJugada_9_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,3,blanca).
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    //trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(1, 1, TableroReversiHex::Ficha::blanca);
    // la (2,3) es la que se intenta validar
    EXPECT_FALSE(trp_anulado5.validarJugada(2, 3, TableroReversiHex::Ficha::blanca));
}

// EFE: Prueba validarJugada(), variante #10-false no hay flanqueo.
TEST_F(PruebasLab1, validarJugada_10_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (5,3,blanca).
    trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 4, TableroReversiHex::Ficha::negra);
    // trp_anulado7.colocarSimple(5, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 1, TableroReversiHex::Ficha::negra);
    // la (5,3,blanca) es la que se intenta validar
    EXPECT_FALSE(trp_anulado7.validarJugada(5, 3, TableroReversiHex::Ficha::blanca));
}

// EFE: Prueba validarJugada(), variante #11-true, con 3 direcciones.
TEST_F(PruebasLab1, validarJugada_11_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (0,3,blanca).
     // trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(3, 1, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    // la (0,3) es la que se intenta validar
    EXPECT_TRUE(trp_anulado5.validarJugada(0, 3, TableroReversiHex::Ficha::blanca));
}


// EFE: Prueba validarJugada(), variante #12-true, con 3 direccciones.
TEST_F(PruebasLab1, validarJugada_12_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (5,4,blanca).
   // trp_anulado7.colocarSimple(5, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 5, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 5, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 6, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(4, 4, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 2, TableroReversiHex::Ficha::blanca);
    // la (5,4,blanca) es la que se intenta validar
    EXPECT_TRUE(trp_anulado7.validarJugada(5, 4, TableroReversiHex::Ficha::blanca));
}
    //EFE: Prueba FlanqueaDir, variante #1, direccion 1.
TEST_F(PruebasLab1, flanqueaDir_1_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,2,blanca).
    trp_anulado5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::blanca);
    if (trp_anulado5.verFlanqueaDir(2, 3, 3, TableroReversiHex::Ficha::negra))
        trp_anulado5.flanqueaDir(2, 3, 3, TableroReversiHex::Ficha::negra);
    // la (2,2) es la que se intenta validar
    EXPECT_FALSE(trp_anulado5.verFichaEn(2, 3) == 2);
}

// EFE: Prueba flanqueaDir(), variante #2-false, dirección 1.
TEST_F(PruebasLab1, flanqueaDir_2_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (6,3,blanca).
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    if (trp_anulado7.verFlanqueaDir(1, 6, 3, TableroReversiHex::Ficha::blanca))
        (trp_anulado7.flanqueaDir(1, 6, 3, TableroReversiHex::Ficha::blanca));
    // la (4, 3) se deja anulada
    // la (6, 3) es la que se intenta validar

    EXPECT_FALSE(trp_anulado7.verFichaEn(6, 3) == 1);
}

// EFE: Prueba flanqueaDir(), variante #3-False, dirección 4.
TEST_F(PruebasLab1, flanqueaDir_3_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,3,blanca).
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    //trp_anulado5.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    // la (2,3,blanca) es la que se intenta validar
    if (trp_anulado5.verFlanqueaDir(4, 2, 3, TableroReversiHex::Ficha::negra))
        (trp_anulado5.flanqueaDir(4, 2, 3, TableroReversiHex::Ficha::negra));

    EXPECT_FALSE(trp_anulado5.verFichaEn(2, 3) == 2);
}

// EFE: Prueba flanqueaDir(), variante #4-false, dirección 4.
TEST_F(PruebasLab1, flanqueaDir_4_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (0,4,blanca).
    trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    //trp_anulado7.colocarSimple(4, 4, TableroReversiHex::Ficha::negra);
    // la(2, 4) se deja anulada
    // la (0,4,blanca) es la que se intenta validar
    if (trp_anulado7.verFlanqueaDir(4, 0, 4, TableroReversiHex::Ficha::blanca))
        (trp_anulado7.flanqueaDir(4, 0, 4, TableroReversiHex::Ficha::blanca));

    EXPECT_FALSE(trp_anulado7.verFichaEn(0, 4) == 2);
}

// EFE: Prueba flanqueaDir(), variante #5-false, dirección 0.
TEST_F(PruebasLab1, flanqueaDir_5_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,1,blanca).
    trp_anulado5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    // la (3, 1) se deja anulada
    // la (4,1) es la que se intenta validar
    if (trp_anulado5.verFlanqueaDir(0, 4, 1, TableroReversiHex::Ficha::blanca))
        (trp_anulado5.flanqueaDir(0, 4, 1, TableroReversiHex::Ficha::blanca));
    EXPECT_FALSE(trp_anulado5.verFichaEn(4, 1) == 1);
}

// EFE: Prueba flanqueaDir(), variante #6-true, dirección 0.
TEST_F(PruebasLab1, flanqueaDir_6_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,3,blanca).
    trp_anulado7.colocarSimple(0, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
    //trp_anulado7.colocarSimple(2, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 1, TableroReversiHex::Ficha::blanca);
    // la (2,3,blanca) es la que se intenta validar
    if (trp_anulado7.verFlanqueaDir(0, 2, 3, TableroReversiHex::Ficha::blanca))
        (trp_anulado7.flanqueaDir(0, 2, 3, TableroReversiHex::Ficha::blanca));

    EXPECT_TRUE(trp_anulado7.verFichaEn(3, 2) == 1);
}

// EFE: Prueba flanqueaDir(), variante #7-true, dirección 2.
TEST_F(PruebasLab1, flanqueaDir_7_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (1,1,blanca).
    trp_anulado5.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    //trp_anulado5.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);
    // la (1,1) es la que se intenta validar
    if (trp_anulado5.verFlanqueaDir(2, 1, 1, TableroReversiHex::Ficha::blanca))
        (trp_anulado5.flanqueaDir(2, 1, 1, TableroReversiHex::Ficha::blanca));
    EXPECT_TRUE(trp_anulado5.verFichaEn(2, 2) == 1);
}
 
// EFE: Prueba flanqueaDir(), variante #8-true, dirección 2.
TEST_F(PruebasLab1, flanqueaDir_8_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (1,1,blanca).
    trp_anulado7.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
    // trp_anulado7.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(5, 3, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(6, 4, TableroReversiHex::Ficha::blanca);
    // la (1,1,blanca) es la que se intenta validar
    if (trp_anulado7.verFlanqueaDir(2, 1, 1, TableroReversiHex::Ficha::blanca))
        (trp_anulado7.flanqueaDir(2, 1, 1, TableroReversiHex::Ficha::blanca));
    EXPECT_TRUE(trp_anulado7.verFichaEn(2, 2) == 1);
}

// EFE: Prueba flanqueaDir(), variante #9-true, dirección 2.
TEST_F(PruebasLab1, flanqueaDir_9_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,1,blanca).
    trp_anulado5.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);
    // trp_anulado5.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
    // la (3,1) es la que se intenta validar
    if (trp_anulado5.verFlanqueaDir(5, 3, 1, TableroReversiHex::Ficha::blanca))
        (trp_anulado5.flanqueaDir(5, 3, 1, TableroReversiHex::Ficha::blanca));
    EXPECT_TRUE(trp_anulado5.verFichaEn(2, 1) == 1);
}

// EFE: Prueba flanqueaDir(), variante #10-false, dirección 5.
TEST_F(PruebasLab1, flanqueaDir_10_f)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,2,blanca).
    trp_anulado7.colocarSimple(6, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
    // la(0, 0) se deja anulada
    // la (4,2,blanca) es la que se intenta validar
    if (trp_anulado7.verFlanqueaDir(5, 4, 2, TableroReversiHex::Ficha::blanca))
        (trp_anulado7.flanqueaDir(5, 4, 2, TableroReversiHex::Ficha::blanca));
    EXPECT_FALSE(trp_anulado7.verFichaEn(3, 1) == 1);
}

// EFE: Prueba flanqueaDir(), variante #11-true, dirección 3.
TEST_F(PruebasLab1, flanqueaDir_11_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (2,1,blanca).
    trp_anulado5.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);
    trp_anulado5.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
    // trp_anulado5.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(1, 1, TableroReversiHex::Ficha::negra);
    trp_anulado5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
    // la (2,1) es la que se intenta validar
    if (trp_anulado5.verFlanqueaDir(3, 2, 1, TableroReversiHex::Ficha::blanca))
        (trp_anulado5.flanqueaDir(3, 2, 1, TableroReversiHex::Ficha::blanca));
    EXPECT_TRUE(trp_anulado5.verFichaEn(1, 1) == 1);
}
// EFE: Prueba flanqueaDir(), variante #12-true, dirección 3.
TEST_F(PruebasLab1, flanqueaDir_12_t)
{
    // Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,1,blanca).
    trp_anulado7.colocarSimple(6, 0, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 0, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 1, TableroReversiHex::Ficha::negra);
    //trp_anulado7.colocarSimple(3, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    // la (3,1,blanca) es la que se intenta validar
    if (trp_anulado7.verFlanqueaDir(3, 3, 1, TableroReversiHex::Ficha::blanca))
        (trp_anulado7.flanqueaDir(3, 3, 1, TableroReversiHex::Ficha::blanca));

    EXPECT_TRUE(trp_anulado7.verFichaEn(2, 2) == 1);
}


//EFE: Prueba adysToString() , variante #1, el metodo imprime toda la serie de strings como deberia ser.
TEST_F(PruebasLab1, adysToString_f){

    EXPECT_FALSE(trp_anulado7.adysToString()._Equal(" "));
}

//EFE: Prueba adysToString() , variante #2, el metodo imprime toda la serie de strings como deberia ser.
TEST_F(PruebasLab1, adysToString_2_f) {

    trp_anulado7.colocarSimple(6, 0, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 0, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    EXPECT_FALSE(trp_anulado7.adysToString()._Equal(" Adyacencias de [0,0]:  { 2, 0 } { 1, 0 }"));

}

//EFE: Prueba adysToString() , variante #3, el metodo imprime toda la serie de strings como deberia ser.
TEST_F(PruebasLab1, adysToString_3_f) {

    trp_anulado7.colocarSimple(6, 0, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(5, 0, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(4, 1, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(1, 2, TableroReversiHex::Ficha::negra);
    trp_anulado7.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(0, 4, TableroReversiHex::Ficha::blanca);
    trp_anulado7.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
    EXPECT_FALSE(trp_anulado7.adysToString()._Equal(" Adyacencias de [0,0]:  { 2, 0 } { 1, 0 } Adyacencias de [0,1]:  { 1, 0 } { 2, 1 } { 1, 1 }"));
}

//EFE: Prueba obtAdys() , variante #1, ficha esquinera.
TEST_F(PruebasLab1, obtAdys_t) {

    vector <LstAdys::DatosAdy> v_dady;
    trp_anulado7.columnas[0][0].lista_adys.obtAdys(v_dady);
    EXPECT_TRUE(trp_anulado7.columnas[0][0].lista_adys.lista.size() == 2);
}

//EFE: Prueba obtAdys() , variante #2, ficha central
TEST_F(PruebasLab1, obtAdys_2_t) {

    vector <LstAdys::DatosAdy> v_dady;
    trp_anulado7.columnas[2][2].lista_adys.obtAdys(v_dady);
    EXPECT_TRUE(trp_anulado7.columnas[2][2].lista_adys.lista.size() == 6);
}

//EFE: Prueba jugarInteligente() , variante #1, jugadaInicial, heuristica 1;
TEST_F(PruebasLab1, jugarInteligente_t) {

    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_TRUE(trp7.columnas[6][3].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #2, jugadaInicial, heuristica 1;
TEST_F(PruebasLab1, jugarInteligente_2_f) {

    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_FALSE(trp7.columnas[5][3].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #4, jugadaInicial, heuristica 3;
TEST_F(PruebasLab1, jugarInteligente_3_t) {

    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp7.jugarInteligente(TableroReversiHex::Ficha::blanca);
    EXPECT_TRUE(trp7.columnas[1][2].cf == 1);
}

//EFE: Prueba jugarInteligente() , variante #4,  heuristica 1;
TEST_F(PruebasLab1, jugarInteligente_4_t) {

    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp7.jugarInteligente(TableroReversiHex::Ficha::blanca);
    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_TRUE(trp7.columnas[0][3].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #5,  heuristica 3;
TEST_F(PruebasLab1, jugarInteligente_5_t) {

    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp7.jugarInteligente(TableroReversiHex::Ficha::blanca);
    trp7.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp7.jugarInteligente(TableroReversiHex::Ficha::blanca);
    EXPECT_TRUE(trp7.columnas[5][2].cf == 1);
}

//EFE: Prueba jugarInteligente() , variante #6, jugadaInicial, heuristica 2;
TEST_F(PruebasLab1, jugarInteligente_6_t) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_TRUE(trp5.columnas[2][3].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #7, jugadaInicial, heuristica 2;
TEST_F(PruebasLab1, jugarInteligente_7_f) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_FALSE(trp5.columnas[2][1].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #8, jugadaInicial, heuristica 2;
TEST_F(PruebasLab1, jugarInteligente_8_f) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp5.jugarInteligente(TableroReversiHex::Ficha::blanca);
    EXPECT_FALSE(trp5.columnas[1][3].cf == 1);
}

//EFE: Prueba jugarInteligente() , variante #9, jugadaInicial, heuristica 2;
TEST_F(PruebasLab1, jugarInteligente_9_t) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp5.jugarInteligente(TableroReversiHex::Ficha::blanca);
    EXPECT_TRUE(trp5.columnas[2][1].cf == 1);
}

//EFE: Prueba jugarInteligente() , variante #10, jugadaInicial, heuristica 3;
TEST_F(PruebasLab1, jugarInteligente_10_t) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp5.jugarInteligente(TableroReversiHex::Ficha::blanca);
    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_TRUE(trp5.columnas[3][0].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #11, jugadaInicial, heuristica 1;
TEST_F(PruebasLab1, jugarInteligente_11_f) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp5.jugarInteligente(TableroReversiHex::Ficha::blanca);
    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_FALSE(trp5.columnas[0][0].cf == 2);
}

//EFE: Prueba jugarInteligente() , variante #12, jugadaInicial, heuristica 1;
TEST_F(PruebasLab1, jugarInteligente_12_f) {

    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    trp5.jugarInteligente(TableroReversiHex::Ficha::blanca);
    trp5.jugarInteligente(TableroReversiHex::Ficha::negra);
    EXPECT_FALSE(trp5.columnas[1][2].cf == 1);
}

// EFE: Prueba obtDatosAdys variante #1.
TEST_F(PruebasLab1, obtDatosAdys_1_t)
{
    LstAdys::DatosAdy v;
    v.c = 0;
    v.p = 0;
    v.dir = 4;
    trp5.columnas[0][0].lista_adys.obtDatosAdy(v);

    EXPECT_TRUE(v.c == 0 && v.p == 0 && v.dir == -1);

}
// EFE: Prueba obtDatosAdys variante #2.
TEST_F(PruebasLab1, obtDatosAdys_2_t)
{
    LstAdys::DatosAdy v;
    v.c = 1;
    v.p = 1;
    v.dir = 1;
    trp5.columnas[1][1].lista_adys.obtDatosAdy(v);

    EXPECT_TRUE(v.c == 3 && v.p == 1 && v.dir == 1);

}
// EFE: Prueba obtDatosAdys variante #3.
TEST_F(PruebasLab1, obtDatosAdys_3_t)
{
    LstAdys::DatosAdy v;
    v.c = 2;
    v.p = 1;
    v.dir = 1;
    trp5.columnas[2][1].lista_adys.obtDatosAdy(v);

    EXPECT_TRUE(v.c == 4 && v.p == 1 && v.dir == 1);

}



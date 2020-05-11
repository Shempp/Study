package main

import (
	"fmt"
	"math"
)

// На уровне пакета (не инициализированы, знач. по умолч.)
var c, python, java bool

// Инициализированы
var i2, j2 int = 1, 2

func main() {
	// На уровне функции (не инициализирована, знач. по умолч.)
	var i int
	fmt.Println(i, c, python, java)

	// Инициализированы
	var c2, python2, java2 = true, false, "no!"
	fmt.Println(i2, j2, c2, python2, java2)

	// Другая форма объявления
	k3 := 3
	c3, python3, java3 := true, false, "no!"

	fmt.Println(k3, c3, python3, java3)

	// Значения по умолчанию
	var i4 int     // 0
	var f4 float64 // 0
	var b4 bool    // false
	var s4 string  // ""
	fmt.Printf("%v %v %v %q\n", i4, f4, b4, s4)

	// Приведение типа
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z uint = uint(f) // Без явного приведения типов будет ошибка
	fmt.Println(x, y, z)

	// Выведение типа (авто)
	i5 := 42           // int
	f5 := 3.142        // float64
	g5 := 0.867 + 0.5i // complex128
	fmt.Println(i5, f5, g5)

	// Константы
	const pi = 3.14
	//const pi := 3.14 // Ошибка
}

package main

import (
	"fmt"
	"math"
)

type MyFloat float64

func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

type Vertex struct {
	X, Y float64
}

// Метод - это функция со специальным аргументом, известным как получатель
func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func Abs(v Vertex) float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

// Через указатель - модификация без копии, без него копия без модификации исх. объекта
func (v *Vertex) Scale(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

func ScaleFunc(v *Vertex, f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

func AbsFunc(v Vertex) float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
	v := Vertex{3, 4}
	// Метод
	fmt.Println(v.Abs())

	// Функция
	fmt.Println(Abs(v))

	// Метод не только для структуры
	f := MyFloat(-math.Sqrt2)
	fmt.Println(f.Abs())

	// Получатели и указатели
	v.Scale(10)
	fmt.Println(v.Abs())

	// Методы и косвенная адресация указателей
	v2 := Vertex{3, 4}
	v2.Scale(2) // (&v).Scale(2)
	ScaleFunc(&v2, 10)

	p2 := &Vertex{4, 3}
	p2.Scale(3)
	ScaleFunc(p2, 8)

	fmt.Println(v2, p2)

	// Методы и косвенная адресация указателей в обратном направлении
	v3 := Vertex{3, 4}
	fmt.Println(v3.Abs())
	fmt.Println(AbsFunc(v3))

	p3 := &Vertex{4, 3}
	fmt.Println(p3.Abs()) // (*p).Abs()
	fmt.Println(AbsFunc(*p3))
}

package main

import "fmt"

// Пример функции
func add(x int, y int) int {
	return x + y
}

// Или так:
/*
func add(x, y int) int {
	return x + y
}
*/

// Множественные результаты:
func swap(x, y string) (string, string) {
	return y, x
}

// Именованные возвращаемые значения
func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func main() {
	fmt.Println(add(42, 13))

	a, b := swap("hello", "world")
	fmt.Println(a, b)

	fmt.Println(split(17))
}

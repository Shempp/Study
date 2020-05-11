package main

import "fmt"

func main() {
	fmt.Println("counting")

	for i := 0; i < 10; i++ {
		// Похож на деструктор в c++ (отложенный вызов, выполняется на момент выхода из функции)
		// Аргументы отложенных вызовов вычисляются сразу же, но вызов функции не происходит до того
		// LIFO
		defer fmt.Println(i)
	}

	fmt.Println("done")
}

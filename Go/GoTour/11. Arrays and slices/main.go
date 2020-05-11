package main

import (
	"fmt"
	"strings"
)

func printSlice(s []int) {
	fmt.Printf("len=%d cap=%d %v\n", len(s), cap(s), s)
}

func PrintSlice(s string, x []int) {
	fmt.Printf("%s len=%d cap=%d %v\n",
		s, len(x), cap(x), x)
}

func main() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println(a)

	// Массив
	primes := [6]int{2, 3, 5, 7, 11, 13}
	fmt.Println(primes)

	// Срез
	var s []int = primes[1:4]
	fmt.Println(s)

	// Срезы это как указатели на массивы
	names := [4]string{
		"John",
		"Paul",
		"George",
		"Ringo",
	}
	fmt.Println(names)

	a2 := names[0:2]
	b2 := names[1:3]
	fmt.Println(a2, b2)

	b2[0] = "XXX"
	fmt.Println(a2, b2)
	fmt.Println(names)

	// Литералы срезов
	q := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(q)

	r := []bool{true, false, true, true, false, true}
	fmt.Println(r)

	s2 := []struct {
		i int
		b bool
	}{
		{2, true},
		{3, false},
		{5, true},
		{7, true},
		{11, false},
		{13, true},
	}
	fmt.Println(s2)

	// Значения по умолчанию в срезах
	s3 := []int{2, 3, 5, 7, 11, 13}

	s3 = s[1:4]
	fmt.Println(s3)

	s3 = s[:2]
	fmt.Println(s3)

	s3 = s[1:]
	fmt.Println(s3)

	// Размер и вместимость среза
	s4 := []int{2, 3, 5, 7, 11, 13}
	printSlice(s4)

	// Slice the slice to give it zero length.
	s4 = s4[:0]
	printSlice(s4)

	// Extend its length.
	s4 = s4[:4]
	printSlice(s4)

	// Drop its first two values.
	s4 = s4[2:]
	printSlice(s4)

	//s4 = s4[0:7] // panic (overflow)
	//printSlice(s4)

	// Нулевые срезы
	var sEmpty []int
	fmt.Println(sEmpty, len(sEmpty), cap(sEmpty))
	if sEmpty == nil {
		fmt.Println("nil!")
	}

	// Создание среза с помощью make
	a1 := make([]int, 5)
	PrintSlice("a1", a1)

	b1 := make([]int, 0, 5)
	PrintSlice("b1", b1)

	c1 := b1[:2]
	PrintSlice("c1", c1)

	d1 := c1[2:5]
	PrintSlice("d1", d1)

	// Срезы срезов
	board := [][]string{
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
	}

	// The players take turns.
	board[0][0] = "X"
	board[2][2] = "O"
	board[1][2] = "X"
	board[1][0] = "O"
	board[0][2] = "X"

	for i := 0; i < len(board); i++ {
		fmt.Printf("%s\n", strings.Join(board[i], " "))
	}

	// Добавление к срезу
	var sAppend []int
	printSlice(sAppend)

	// append works on nil slices.
	sAppend = append(sAppend, 0)
	printSlice(sAppend)

	// The slice grows as needed.
	sAppend = append(sAppend, 1)
	printSlice(sAppend)

	// We can add more than one element at a time.
	sAppend = append(sAppend, 2, 3, 4)
	printSlice(sAppend)
}

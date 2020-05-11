package main

import (
	"fmt"
	"math"
)

func sqrt(x float64) string {
	if x < 0 {
		return sqrt(-x) + "i"
	}
	return fmt.Sprint(math.Sqrt(x))
}

func pow(x, n, lim float64) float64 {
	if v := math.Pow(x, n); v < lim {
		return v
	} else {
		fmt.Printf("%g >= %g\n", v, lim)
	}
	// Переменная v недоступна тут
	return lim
}

func Sqrt(x float64) float64 {
	result := 1.0
	for i := result; i < 10; i++ {
		sqrtVar := result - (result*result-x)/(2*result)
		if result-sqrtVar > 0 {
			if result-sqrtVar <= 1e-15 {
				return sqrtVar
			}
		}
		result = sqrtVar
	}

	return result
}

func main() {
	fmt.Println(sqrt(2), sqrt(-4))

	fmt.Println(
		pow(3, 2, 10),
		pow(3, 3, 20),
	)

	fmt.Println(Sqrt(2))
}

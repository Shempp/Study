package main

import "fmt"

type Vertex struct {
	Lat, Long float64
}

// nil
var m map[string]Vertex

// Литералы карт
var m2 = map[string]Vertex{
	"Bell Labs": Vertex{
		40.68433, -74.39967,
	},
	"Google": Vertex{
		37.42202, -122.08408,
	},
}

// Другой вариант
var m3 = map[string]Vertex{
	"Bell Labs": {40.68433, -74.39967},
	"Google":    {37.42202, -122.08408},
}

func main() {
	m = make(map[string]Vertex)
	m["Bell Labs"] = Vertex{
		40.68433, -74.39967,
	}
	fmt.Println(m["Bell Labs"])

	fmt.Println(m2)

	fmt.Println(m3)

	// Изменения карт
	m4 := make(map[string]int)

	m4["Answer"] = 42
	fmt.Println("The value:", m["Answer"])

	m4["Answer"] = 48
	fmt.Println("The value:", m["Answer"])

	delete(m4, "Answer")
	fmt.Println("The value:", m["Answer"])

	v, ok := m4["Answer"]
	fmt.Println("The value:", v, "Present?", ok)
}

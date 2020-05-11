package main

import "fmt"

type Vertex struct {
	X int
	Y int
}

// Литералы структур
var (
	v1      = Vertex{1, 2}  // has type Vertex
	v2      = Vertex{X: 1}  // Y:0 is implicit
	v3      = Vertex{}      // X:0 and Y:0
	pointer = &Vertex{1, 2} // has type *Vertex
)

func main() {
	v := Vertex{1, 2}
	v.X = 4
	fmt.Println(v.X)

	// Через указатели
	v4 := Vertex{1, 2}
	p := &v4
	p.X = 1e9 // (*p).X
	fmt.Println(v4)

	fmt.Println(v1, pointer, v2, v3)
}

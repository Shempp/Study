package main

import (
	"fmt"
	"io"
	"os"
	"strings"
	"time"
)

type MyError struct {
	When time.Time
	What string
}

func (e *MyError) Error() string {
	return fmt.Sprintf("at %v, %s",
		e.When, e.What)
}

func run() error {
	return &MyError{
		time.Now(),
		"it didn't work",
	}
}

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("cannot Sqrt negative number: %v/n", float64(e))
}

func Sqrt(x float64) (float64, error) {
	if x < 0 {
		return 0, ErrNegativeSqrt(x)
	}

	result := 1.0
	for i := result; i < 10; i++ {
		sqrtVar := result - (result*result-x)/(2*result)
		if result-sqrtVar > 0 {
			if result-sqrtVar <= 1e-15 {
				return sqrtVar, nil
			}
		}
		result = sqrtVar
	}

	return result, nil
}

type rot13Reader struct {
	r io.Reader
}

func (r13 *rot13Reader) Read(p []byte) (int, error) {
	n, err := r13.r.Read(p)
	for i := 0; i < n; i++ {
		c := p[i] | 0x20 // lowercase byte
		if 'a' <= c && c <= 'm' {
			p[i] += 13
		} else if 'n' <= c && c <= 'z' {
			p[i] -= 13
		}
	}
	return n, err
}

func main() {
	if err := run(); err != nil {
		fmt.Println(err)
	}

	// Упражнение: ошибки
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))

	r := strings.NewReader("Hello, Reader!")

	b := make([]byte, 8)
	for {
		n, err := r.Read(b)
		fmt.Printf("n = %v err = %v b = %v\n", n, err, b)
		fmt.Printf("b[:n] = %q\n", b[:n])
		if err == io.EOF {
			break
		}
	}

	// Упражнение: rot13Reader
	s2 := strings.NewReader("Lbh penpxrq gur pbqr!")
	r2 := rot13Reader{s2}
	io.Copy(os.Stdout, &r2)
}

package main

import (
	"fmt"
	"math/big"
)

func Multi(numOfStroke int, m big.Rat, matrix [][]big.Rat){
	for i := 0; i < len(matrix[numOfStroke]); i++{
		matrix[numOfStroke][i] = *new(big.Rat).Mul(&matrix[numOfStroke][i], &m)
	}
}

func Div(numOfStroke int, m big.Rat, matrix [][]big.Rat){
	for i := 0; i < len(matrix[numOfStroke]); i++{
		matrix[numOfStroke][i] = *new(big.Rat).Quo(&matrix[numOfStroke][i], &m)
	}
}

func Add(first, second int, matrix [][]big.Rat){
	for i := 0; i < len(matrix[first]); i++{
		matrix[first][i] = *new(big.Rat).Add(&matrix[first][i], &matrix[second][i])
	}
}

func Sub(first, second int, matrix [][]big.Rat){
	for i := 0; i < len(matrix[first]); i++{
		matrix[first][i] = *new(big.Rat).Sub(&matrix[first][i], &matrix[second][i])
	}
}

func main(){
	var n int
	fmt.Scan(&n)
	matrix := make([][]big.Rat, n)
	for i := 0; i < n; i++{
		matrix[i] = make([]big.Rat, n+1)
		for j := 0; j <= n; j++{
			var s string
			fmt.Scan(&s)
			matrix[i][j].SetString(s)
		}
	}
	
	for i := 0; i < n; i++{
		if matrix[i][i].Num().Int64() != 0 {
			Div(i, matrix[i][i], matrix)
		} else {
			flag := false
			for k := 0; k < n; k++{
				if matrix[k][i].Num().Int64() != 0{
					Add(i, k, matrix)
					Div(i, matrix[i][i], matrix)
					flag = true
					break
				}
			}
			if !flag {
				continue
			}
		}
		for j := 0; j < n; j++{
			if i == j{
				continue
			} else {
				if matrix[j][i].Num().Int64() != 0{
					Multi(i, matrix[j][i], matrix)
					Sub(j, i, matrix)
					Div(i, matrix[i][i], matrix)
				}
			}
		}
	}
	
	flag := true
	for i := 0; i < n; i++ {
		if matrix[i][i].Num().Int64() == 0{
			fmt.Println("No solution")
			flag = false
			break
		}
	}
	
	if flag{
		for i := 0; i < n; i++ {
			fmt.Println(matrix[i][n].String())
		}
	}
}
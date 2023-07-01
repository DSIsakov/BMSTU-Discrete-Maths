package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func scanOp(i *int, str []string) int {
	if str[*i] == "+"{
		*i++
		a := scanOp(i, str)
		b := scanOp(i, str)
		
		return a + b
	} else if str[*i] == "-"{
		*i++
		a := scanOp(i, str)
		b := scanOp(i, str)
		
		return a - b
	} else if str[*i] == "*"{
		*i++
		a := scanOp(i, str)
		b := scanOp(i, str)
		
		return a * b
	} else {
		a, _ := strconv.Atoi(str[*i])
		*i++
		return a
	}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	str, _ := reader.ReadString('\n')
	str = strings.ReplaceAll(str, " ", "")
	str = strings.ReplaceAll(str, "(", "")
	str = strings.ReplaceAll(str, ")", "")
	str = strings.TrimSpace(str)
	chars := strings.Split(str, "")
	i := 0
	
	fmt.Println(scanOp(&i, chars))
}
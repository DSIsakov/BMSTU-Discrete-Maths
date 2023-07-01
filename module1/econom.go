package main

import (
	"fmt"
)

func scanOp(start int, current *int, computed *map[string]bool, str string, count *int){
	*current++
	for ; string(str[*current]) != ")"; *current++ {
		if (string(str[*current]) == "("){
			scanOp(*current, current, computed, str, count)
		}
	}
	if _, ok := (*computed)[str[start:*current+1]]; !ok {
		(*computed)[str[start:*current+1]] = true
		*count++
	}
}

func main(){
	var str string
	fmt.Scanln(&str)
	computed := map[string]bool{}
	current := 0
	count := 0
	
	if string(str[0]) == "("{
		scanOp(0, &current, &computed, str, &count)
	}
	
	fmt.Println(count)
}
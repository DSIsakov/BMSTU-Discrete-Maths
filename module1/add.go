package main

func main(){}

func add(a, b []int32, p int) []int32 {
	size := 0
	if len(a) < len(b) {
		size = len(b)
	} else {
		size = len(a)
	}
	
	result := make([]int32, size)
	p32 := int32(p)
	newa := make([]int32, size)
	copy(newa, a)
	newb := make([]int32, size)
	copy(newb, b)
	
	temp := int32(0)
	for i := 0; i < size; i++ {
		result[i] = (newa[i] + newb[i] + temp) % p32
		temp = (newa[i] + newb[i] + temp) / p32
	}
	
	if temp != 0 {
		result = append(result, temp)
	}
	
	return result
}

	
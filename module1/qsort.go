package main

func main(){}

func part(left, right int, less func(i, j int) bool, swap func(i, j int)) int{
	i := left
	j := left
	for ; j < right; j++ {
		if less(j, right){
			swap(i, j)
			i++
		}
	}
	swap(i, right)
	return i
}

func qsortrec(left, right int, less func(i, j int) bool, swap func(i, j int)){
	if left < right{
		q := part(left, right, less, swap)
		qsortrec(left, q-1, less, swap)
		qsortrec(q+1, right, less, swap)
	}
}

func qsort(n int, less func(i, j int) bool, swap func(i, j int)){
	qsortrec(0, n-1, less, swap)
}
#define ULONG_BIT 64


unsigned long getbits(unsigned long data[], unsigned index, unsigned length){
    unsigned int start_index = index/ULONG_BIT;
    unsigned int finish_index = (index + length - 1)/ULONG_BIT;
    if(start_index == finish_index){
        if(length%ULONG_BIT == 0){
            return data[start_index];
        }
        unsigned long mask = (((1UL << (length))) << index)-1UL;
        return (data[start_index] & mask) >> index;
    }else{
       unsigned long mask = (((1UL << (ULONG_BIT - index))) << index)-1UL;
       unsigned long first_value = (data[start_index] & mask) >> index;
       mask = (1UL << (length + index - ULONG_BIT)) -1UL;
       unsigned long second_value = (data[finish_index] & mask) << (ULONG_BIT - index);
       return first_value | second_value;
    }
}

void setbits(unsigned long data[], unsigned index, unsigned length, unsigned long value){
    unsigned int start_index = index/ULONG_BIT;
    unsigned int finish_index = (index + length - 1)/ULONG_BIT;
    if(start_index == finish_index){
        if(length%ULONG_BIT == 0){
            data[start_index] = data[start_index] + value;
        }
        unsigned long lower_mask = ((1UL << index)-1UL); //get the lower part of the mask (before index)
        unsigned long higher_mask = ((1UL<< (ULONG_BIT - index - length))-1UL) << (index + length); // get the higher part of the mask (after index)
        unsigned long mask = higher_mask | lower_mask; //join the two halfs
        unsigned long value_to_write = value << index; //set value to the correct index position
        data[start_index] = (data[start_index] & mask) | value_to_write; //write the value after setting the wanted bits to 0 using the previously created mask
    } else{
        unsigned long first_value_mask = (1UL << (ULONG_BIT - index)) - 1UL; //get the mask for the portion of the value to be written on the first value of the array
        unsigned long first_value = value & first_value_mask; //get the portion of the value using previously created mask
        unsigned long lower_mask = ((1UL << index)-1UL); //get the mask for where the value is supposed to be written to
        data[start_index] = (data[start_index] & lower_mask) | (first_value << index); //write the value
        unsigned long second_value_mask = ((1UL << (length - (ULONG_BIT - index))) -1UL) << (ULONG_BIT - index); //get the mask for the remaining portion of the value to be written to the second position of the array
        unsigned long second_value = (value & second_value_mask) >> (ULONG_BIT - index); //get the remaining value using its mask
        unsigned long higher_mask = ((1UL<< (ULONG_BIT - (index + length - ULONG_BIT)))-1UL) << (index + length - ULONG_BIT); //get the mask for the portion of the second position of the array to be writen
        data[finish_index] = (data[finish_index] & higher_mask) | second_value; //write the value
    }
}
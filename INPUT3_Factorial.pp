// Mold Example 3: Testing numbers (ex: factorial)

fn main() {
    let mut i: i32;
    let mut n: i32;
    let mut f: i32;
    
    f = 1;
    i = 1;
    
    println!("Write a number:");
    n = read_input();
    
    while i < n {
        f = f * i;
        i = i + 1;
    }
    
    println!("Factorial:");
    println!("{}", f);
}

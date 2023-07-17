// PePe Example 2: Volume of a sphere

fn main() {
    let mut pi: f64;
    let mut r: f64;
    let mut vol: f64;
    
    pi = 3.14;
    
    println!("Enter the radius:");
    r = read_input();
    
    vol = 4.0 / 3.0 * pi * (r * r * r);
    
    println!("The volume of the sphere is: {}", vol);
}
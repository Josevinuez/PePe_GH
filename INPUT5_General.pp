// PePe Example 5
// The program is "lexically" correct and should not generate any error (based on Platypus from Svillen Ranev)

fn main() {
    let mut i: i32;
    let mut a: f64;
    let mut sum008: f64;
    let mut text: String;

    a = 1.2;
    sum008 = 7.87050;
    input(&mut a, &mut sum008);
    i = 0;
    
    while i < 32767 || i == 32767 {
        i = i + 2;
        a = a * i as f64 / 0.5;
        sum008 = sum008 + a - 1;
    }
    
    if text == "" {
        text = "prog".to_string() + "ram";
    } else {
        text = text + "ram";
    }
    
    println!("\\* This is a program -:)-<-<-- *\\");
    println!("{}", text);
    
    if text != "program" && sum008 == 8.0 || i > 10 {
        println!("{}", sum008);
        println!();
    }
}
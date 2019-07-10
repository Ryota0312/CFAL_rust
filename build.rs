extern crate cc;

fn main(){
    cc::Build::new()
        .cpp(true)
        .warnings(true)
        .flag("-std=c++11")
        .flag("-Wall")
        .flag("-Wextra")
        .flag("-v")
        .flag("-g")
        .flag("-O3")
        .file("src/cpp/src/fsw.cpp")
        .include("/usr/local/include/libfswatch/c++")
        .include("src/cpp/include")
        .compile("libfsw.a");

    println!("cargo:rustc-link-search=native=/usr/local/lib");
    println!("cargo:rustc-link-lib=fswatch");
}

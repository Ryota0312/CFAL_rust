extern crate libc;

use libc::c_char;
use std::ffi::CString;

#[link(name = "fsw", kind = "static")]
extern "C" {
    fn fsw_test(path: *const c_char);
}

fn main() {
    let path = CString::new("/home/ryota").unwrap();
    
    unsafe{
        fsw_test(path.as_ptr());
    }
}

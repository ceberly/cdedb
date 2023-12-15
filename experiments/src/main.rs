const PAGE_SIZE: usize = 64; // bytes

#[derive(Copy, Clone)]
enum PageKind {
    Root = 0x0,
    Internal = 0x1,
    Leaf = 0x2,
}

struct Page {
    kind: PageKind,
    cell_pointers: Vec<usize>,
}

impl Page {
    pub fn create(kind: PageKind) -> Self {
        Self {
            kind,
            cell_pointers: vec![],
        }
    }
}

// These traits define the on-disk format of a page
// Also, the format is largely unchecked for correctness.
impl From<&[u8]> for Page {
    fn from(bytes: &[u8]) -> Self {
        if bytes.len() != PAGE_SIZE {
            panic!("malformed page");
        }

        let cell_pointer_len = u16::from_be_bytes(bytes[1..2].try_into().unwrap());

        Self {
            kind: match bytes[0] {
                0x0 => PageKind::Root,
                0x1 => PageKind::Internal,
                0x2 => PageKind::Leaf,
                _ => panic!("malformed page"),
            },
        }
    }
}

struct Store {
    backing: Vec<u8>,
}

impl Store {
    pub fn create() -> Self {
        let mut file = vec![0u8; PAGE_SIZE * 10];

        // prepare the root page
        let root = Page::create(PageKind::Root);
        root.write_to(&mut file);

        Self { backing: file }
    }

    fn page(&self, page_number: usize) -> Page {
        let start = page_number * PAGE_SIZE;
        let end = start + PAGE_SIZE;
        Page::from(&self.backing[start..end])
    }

    pub fn insert(&self, key: u32, val: &[u8]) {
        println!("{}", val.len());
    }

    pub fn get(&self, key: u32) -> Option<&[u8]> {
        Some("ok".as_bytes())
    }
}

fn main() {
    let file = vec![0u8, 12u8, 34u8];

    let page = Page::from(&file);
    println!("${:?}", page);
    //    let store = Store::create();
    //
    //    store.insert(1, "100".as_bytes());
    //    store.insert(2, "200".as_bytes());
    //    store.insert(3, "300".as_bytes());
    //
    //    let v1 = store.get(1);
    //    let v2 = store.get(2);
    //    let v3 = store.get(3);
    //
    //    println!("{:?} {:?} {:?}", v1, v2, v3);
}

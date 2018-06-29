let string_of_file_kind = (kind: Unix.file_kind): string => {
    switch (kind) {
    | Unix.S_REG => "file"
    | Unix.S_DIR => "dir"
    | _ => "other"
    }
};

let run = () => {
    let currentDir = Unix.opendir(Unix.getcwd());

    let break = ref(false);

    while (! break^) {
        switch (Unix.readdir(currentDir)) {
        | exception End_of_file => break := true
        | item =>
            let file_stats: Unix.stats = Unix.stat(item);
            let formatted_item =
                Printf.sprintf(
                    "• %4s - %s",
                    string_of_file_kind(file_stats.st_kind),
                    item
                );
            print_endline(formatted_item);
            
        };
    };

    Unix.closedir(currentDir);
};

run();
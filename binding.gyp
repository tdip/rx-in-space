{
    "targets":[
        {
            "target_name":"libRxInSpace",
            "type":"<(library)",
            "sources":[
                '<!@(find src/cpp/src/shared/ -name "*.cc")',
            ],
            "include_dirs":[
                "<!(node -e \"require('nan')\")",
                "src/cpp/src/shared",
                "src/cpp/src/include",
                "src/cpp/modules/RxCpp/Rx/v2/src"
            ],
            "cflags_cc":[
                "-fexceptions",
                "-std=c++17",
                "-frtti"
            ],
            'defines':[
                'NDEBUG'
            ],
            'conditions':[
                [
                    'OS=="mac"',
                    {
                        'xcode_settings':{
                            'GCC_ENABLE_CPP_RTTI':'YES',
                            'GCC_ENABLE_CPP_EXCEPTIONS':'YES',
                            'CLANG_CXX_LANGUAGE_STANDARD':'c++17'
                        }
                    }
                ]
            ],
        },
        {
            "target_name":"rx_in_space",
            "type":"<(library)",
            "sources":[
                '<!@(find src/cpp/src/platform/ -name "*.cc")',
            ],
            "dependencies": ["libRxInSpace"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
                "src/cpp/src/shared",
                "src/cpp/src/include",
                "src/cpp/src/platform/node/support",
                "src/cpp/modules/RxCpp/Rx/v2/src",
            ],
            "cflags_cc": [
                "-fexceptions",
                "-std=c++17",
                "-frtti"
            ]
        }
    ]
}
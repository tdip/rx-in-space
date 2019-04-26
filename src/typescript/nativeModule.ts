import * as path from "path"
import * as rxjs from "rxjs"

import { OutputSet } from "./core"

const LD_LIBRARY_PATH = 'LD_LIBRARY_PATH';

function RX_IN_SPACE_LIB_PATH(){
    return path.join(__dirname, '..', '..', 'lib');
}

export type ManagedReactiveSpaceMember = rxjs.Observable<any>; 

export type ManagedNativeReactiveSpace = {
    update(set: OutputSet, member: ManagedNativeReactiveSpace);
};

export type RxInSpace = {
    readonly NodeReactiveSpace: {new(rx: typeof rxjs): ManagedNativeReactiveSpace}
}

function loadRxInSpace(): RxInSpace{
    if(process.env[LD_LIBRARY_PATH]){
        process.env[LD_LIBRARY_PATH] = `${process.env[LD_LIBRARY_PATH]}:${RX_IN_SPACE_LIB_PATH()}`;
    }else{
        process.env[LD_LIBRARY_PATH] = RX_IN_SPACE_LIB_PATH();
    }

    return require('../../../lib/rx_in_space.node');
}

export const RxInSpace = loadRxInSpace();
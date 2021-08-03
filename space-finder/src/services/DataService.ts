import { Space } from "../model/Model";

export class DataService {
    
    public async getSpaces(): Promise<Space[]> {
        const result: Space[] = []
        result.push({
            location: 'Holland',
            name: 'Beautiful',
            spaceId: '1'
        });
        result.push({
            location: 'Israel',
            name: 'Amazing',
            spaceId: '2'
        });
        result.push({
            location: 'France',
            name: 'Colorful',
            spaceId: '3'
        });
        return result;
    }

    public async reserveSpace(spaceId: string): Promise<string | undefined>{
        if (spaceId === '1'){
            return('555')
        }else{
            return undefined
        }
    }
}